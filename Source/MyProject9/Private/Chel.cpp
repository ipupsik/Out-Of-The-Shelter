// Fill out your copyright notice in the Description page of Project Settings.


#include "Chel.h"

#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/PoseableMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine.h"
#include "Engine/EngineTypes.h"
#include "Blueprint/UserWidget.h"
#include "Components/SkinnedMeshComponent.h"
#include "AreaCollision.h"
#include "BP_PlayerController.h"

enum PickUpType {
	Boltorez,
	KeyShelter,
	Otvertka
};

// Sets default values
AChel::AChel()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PoseableMeshComp = CreateDefaultSubobject<UPoseableMeshComponent>(TEXT("PoseableMeshComp"));
	PoseableMeshComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(PoseableMeshComp, TEXT("Bone_002_end"));

	Stone = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Stone"));
	Stone->SetupAttachment(CameraComp);

	TimeLineFirst = CreateDefaultSubobject<UTimelineComponent>(TEXT("ThrowStoneFirst"));
	TimeLineSecond = CreateDefaultSubobject<UTimelineComponent>(TEXT("ThrowStoneSecond"));

	//Говорим делегатам, какую функцию подцепить для Update и для OnFinished
	InterpFunction.BindUFunction(this, FName("TimelineFloatReturn"));
	TimelineFinishedFirst.BindUFunction(this, FName("OnTimelineFinished_First"));
	TimelineFinishedSecond.BindUFunction(this, FName("OnTimelineFinished_Second"));

	Health = 0;
	bIsAlreadyThrowing = false;
	IsInGame = false;
	Ammo = 10;
	bLineTrace_is_need_refresh = false;
	DoesHave_Owner = false;
	ItemCodePickUp = -1;
	IsEnableInput = true;

	KillerIndex = -1;
	IsSuccessOpening = false;
	AreaCode = -1;
}

// Called when the game starts or when spawned
void AChel::BeginPlay()
{
	Super::BeginPlay();

	if (GetLocalRole() == ROLE_Authority && UGameplayStatics::GetPlayerController(GetWorld(), 0) == GetController())
	{

	}
	else
		MyBeginPlay();
}

void AChel::MyBeginPlay()
{
	GS = Cast<AGS>(GetWorld()->GetGameState());

	IsServerAuth = GetLocalRole() == ROLE_Authority;
	World = GetWorld();
	IsPlayerOwner = UGameplayStatics::GetPlayerController(GetWorld(), 0) == GetController();

	GI = World->GetGameInstance<UGI>();

	if (vCurve) {
		//Подцепляем эти функции для TimeLine
		TimeLineFirst->AddInterpVector(vCurve, InterpFunction);
		TimeLineFirst->SetTimelineFinishedFunc(TimelineFinishedFirst);

		TimeLineFirst->SetLooping(false);
		TimeLineFirst->SetIgnoreTimeDilation(true);

		TimeLineSecond->AddInterpVector(vCurve, InterpFunction);
		TimeLineSecond->SetTimelineFinishedFunc(TimelineFinishedSecond);

		TimeLineSecond->SetLooping(false);
		TimeLineSecond->SetIgnoreTimeDilation(true);
	}

	if (IsPlayerOwner) {
		UserView = Cast<UUserView>(CreateWidget(World, UserViewClass));
		KillFeed = CreateWidget(World, KillFeedClass);
		UserView->AddToViewport();
		KillFeed->AddToViewport();

		UserView->Player = this;
		UserView->AmmoLabel->SetText(FText::AsNumber((int32)Ammo));

		if (GI != nullptr) {
			//Sensetivity = GI->SGF->Sensetivity;
			//DeliverNicknameToServer(GI->SGF->NickName);
		}
	}

	if (IsServerAuth) {
		Index = GS->AmountOfPlayers++;
		for (int i = 0; i < 2; ++i)
		{
			ASpectator* spec = World->SpawnActorDeferred<ASpectator>(SpectatorClass, CameraComp->GetComponentTransform());
			if (spec != nullptr) {
				spec->Player = this;
				spec->Index = Index;
				spec->Layer = i;
				UGameplayStatics::FinishSpawningActor(spec, CameraComp->GetComponentTransform());
			}
			if (GS != nullptr)
				GS->Spectators.Add(spec);
		}

		DoesHave.Init(false, 3);
	}

	if (IsServerAuth && IsPlayerOwner)
		Cast<ABP_PlayerController>(GetController())->IsHost = true;
}

void AChel::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	MyBeginPlay();
}

// Called every frame
void AChel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsInGame == true) {
		if (IsServerAuth) {
			DeltaTime *= 2 * 0.01f * RadCoeff;
			Health += DeltaTime;
			if (Health > 1.0f) {
				if (DoesHave[Boltorez])
					GS->CurrentBoltorez--;
				if (DoesHave[KeyShelter])
					GS->CurrentKeyShelter--;
				if (DoesHave[Otvertka])
					GS->CurrentOtvertka--;

				TArray<AActor*>Players;
				UGameplayStatics::GetAllActorsOfClass(World, StaticClass(), Players);
				for (auto Player : Players)
					if (KillerIndex != -1)
						Cast<AChel>(Player)->RefreshWidgets(DoesHave, KillerIndex, Index, false);
					else
						Cast<AChel>(Player)->RefreshWidgets(DoesHave, -1, Index, true);
				DoesHave.Init(false, 3);
				KillerIndex = -1;

				KillPlayer();
			}
		}
	}



	if (IsPlayerOwner) {
		UserView->RadiationPoints->SetPercent(Health);
		UserView->DarkScreen->SetRenderOpacity(Health);
	}

	if (IsPlayerOwner) {
		FHitResult OutHit;

		FVector StartLocation = CameraComp->GetComponentLocation();
		FVector EndLocation = StartLocation + CameraComp->GetForwardVector() * 300;

		FCollisionQueryParams CollisionParams;

		//DrawDebugLine(World, StartLocation, EndLocation, FColor::Red, false, 1, 0, 1);

		isTracedBad = false; //Предположим, что мы не нашли лайн трейсом нужные нам предметы
		if (World->LineTraceSingleByChannel(OutHit, StartLocation, EndLocation, ECC_Visibility, CollisionParams))
		{
			if (OutHit.bBlockingHit)
			{
				AActor* HittableActor = OutHit.GetActor();
				if (HittableActor) { //Если мы стукнулись в какой-то актор, а не в пустоту
					APickableItem* TracedItem = Cast<APickableItem>(HittableActor);
					if (TracedItem) { //Если мы стукнулись в нужный нам предмет
						ItemCodePickUp = TracedItem->Type;
						switch (ItemCodePickUp)
						{
							case Boltorez:
							{
								UserView->PickUpLabel_Boltorez->SetVisibility(ESlateVisibility::Visible);

								UserView->PickUpLabel_KeyShelter->SetVisibility(ESlateVisibility::Hidden);
								UserView->PickUpLabel_Otvertka->SetVisibility(ESlateVisibility::Hidden);
								break;
							}
							case KeyShelter:
							{
								UserView->PickUpLabel_KeyShelter->SetVisibility(ESlateVisibility::Visible);

								UserView->PickUpLabel_Boltorez->SetVisibility(ESlateVisibility::Hidden);
								UserView->PickUpLabel_Otvertka->SetVisibility(ESlateVisibility::Hidden);
								break;
							}
							case Otvertka:
							{
								UserView->PickUpLabel_Otvertka->SetVisibility(ESlateVisibility::Visible);

								UserView->PickUpLabel_KeyShelter->SetVisibility(ESlateVisibility::Hidden);
								UserView->PickUpLabel_Boltorez->SetVisibility(ESlateVisibility::Hidden);
								break;
							}
						}
						isTracedBad = false;
						bLineTrace_is_need_refresh = true;  //Говорим, что в текущем кадре мы ударились в нужный предмет
						LastItem = TracedItem;
						LastItem->Item->SetCustomDepthStencilValue(255);
					}
					else
						isTracedBad = true; //Мы не попали в нужный нам предмет
				}
				else
					isTracedBad = true;  //Мы не попали в нужный нам предмет
			}
			else
				isTracedBad = true;  //Мы не попали в нужный нам предмет
		}
		else
			isTracedBad = true;   //Мы не попали в нужный нам предмет

		if (isTracedBad && bLineTrace_is_need_refresh) { 
			//Если мы не попали в нужный нам предмет, но на прошлом кадре мы отрисовали виджет,
			// то для оптимизации мы скрываем все виджеты до первого удачного столкновения с нужным предметом
			bLineTrace_is_need_refresh = false;

			ItemCodePickUp = -1;

			LastItem->Item->SetCustomDepthStencilValue(0);

			UserView->PickUpLabel_KeyShelter->SetVisibility(ESlateVisibility::Hidden);
			UserView->PickUpLabel_Boltorez->SetVisibility(ESlateVisibility::Hidden);
			UserView->PickUpLabel_Otvertka->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

//SetupReplicationVariables----
void AChel::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AChel, Index)
	DOREPLIFETIME(AChel, Health)
	DOREPLIFETIME(AChel, NickName)
	DOREPLIFETIME(AChel, Ammo)
	DOREPLIFETIME(AChel, Death)
	DOREPLIFETIME(AChel, Kills)
	DOREPLIFETIME(AChel, IsEnableInput)
	DOREPLIFETIME(AChel, DoesHave)
}
//-----------------------------

//NicknameSetup----------------
void AChel::DeliverNicknameToServer_Implementation(const FText& newNickName) {
	GS->NickNames[Index] = newNickName;
}

bool AChel::DeliverNicknameToServer_Validate(const FText& newNickName) {
	return true;
}
// Called to bind functionality to input
void AChel::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("GoForward", this, &AChel::GoForward);
	PlayerInputComponent->BindAxis("GoRight", this, &AChel::GoRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AChel::LookUp);
	PlayerInputComponent->BindAxis("LookRight", this, &AChel::LookRight);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AChel::MyJump);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AChel::StartSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AChel::StopSprint);
	PlayerInputComponent->BindAction("KillFeed", IE_Pressed, this, &AChel::ShowKillFeed);
	PlayerInputComponent->BindAction("KillFeed", IE_Released, this, &AChel::UnShowKillFeed);
	PlayerInputComponent->BindAction("ThrowStone", IE_Pressed, this, &AChel::ThrowStone);
	PlayerInputComponent->BindAction("PickUp", IE_Pressed, this, &AChel::PickUp);
	PlayerInputComponent->BindAction("Opening", IE_Pressed, this, &AChel::OpenAreaPressed);
	PlayerInputComponent->BindAction("Opening", IE_Released, this, &AChel::OpenAreaReleased);
}

void AChel::OpenAreaPressed() 
{
	if (AreaCode != -1)
	{
		IsSuccessOpening = true;
		if (!GS->AreaAvaliables[AreaCode] && DoesHave[AreaCode]) {
			UserView->PB_Opening->SetVisibility(ESlateVisibility::Visible);
			UserView->TimeLeft->SetVisibility(ESlateVisibility::Visible);
		}
		switch (AreaCode)
		{
		case Boltorez:
		{
			if (GS->AreaAvaliables[AreaCode])
			{
				PlayerEscape(AreaCode);
				UserView->RemoveFromParent();
			}
			else if (DoesHave[AreaCode])
			{
				UserView->PlayAnimation(UserView->CanalizaciaAnim);
			}
			break;
		}
		case KeyShelter:
		{
			if (GS->AreaAvaliables[AreaCode])
			{
				PlayerEscape(AreaCode);
				UserView->RemoveFromParent();
			}
			else if (DoesHave[AreaCode])
			{
				UserView->PlayAnimation(UserView->ShelterAnim);
			}
			break;
		}
		case Otvertka:
		{
			if (GS->AreaAvaliables[AreaCode])
			{
				PlayerEscape(AreaCode);
				UserView->RemoveFromParent();
			}
			else if (DoesHave[AreaCode])
			{
				UserView->PlayAnimation(UserView->VentilaciaAnim);
			}
			break;
		}
		}
	}
}

void AChel::OpenAreaReleased()
{
	if (AreaCode != -1) {
		if (IsSuccessOpening) {
			IsSuccessOpening = false;
			UserView->StopAllAnimations();
		}
	}
}

//TimelineAnimation
void AChel::OnTimelineFinished_First() {
	ThrowStoneServer(Stone->GetComponentTransform());
	TimeLineSecond->ReverseFromEnd();
}

void AChel::StoneCountUpdate_Implementation()
{
	UserView->AmmoLabel->SetText(FText::AsNumber(Ammo));
}

void AChel::TimelineFloatReturn(FVector value) {
	Stone->SetRelativeLocation(StonePosition + value);
}

void AChel::OnTimelineFinished_Second() {
	bIsAlreadyThrowing = false;
}
//-----------------------------

//AttackInput------------------
void AChel::ThrowStone() {
	if (Ammo > 0 && IsEnableInput) {
		if (!bIsAlreadyThrowing) {
			bIsAlreadyThrowing = true;
			StonePosition = Stone->GetRelativeLocation();

			TimeLineFirst->PlayFromStart();
		}
	}
}

void AChel::ThrowStoneServer_Implementation(FTransform StoneTransform)
{
	--Ammo;
	StoneCountUpdate();
	AStone* NewStone = World->SpawnActorDeferred<AStone>(StoneClass, StoneTransform);
	NewStone->Index = Index;
	UGameplayStatics::FinishSpawningActor(NewStone, StoneTransform);
	if (Ammo == 0) {
		HideStoneMulticast();
	}
}

void AChel::HideStoneMulticast_Implementation() {
	Stone->SetHiddenInGame(true);
}

bool AChel::ThrowStoneServer_Validate(FTransform StoneTransform)
{
	return true;
}
//----------------------------

//KeyBoardInput----------------
void AChel::GoForward(float input) {
	if (input != 0.0f && IsEnableInput) {
		AddMovementInput(GetActorForwardVector(), input * MoveCoeff);
	}
}

void AChel::GoRight(float input) {
	if (input != 0.0f && IsEnableInput) {
		AddMovementInput(GetActorRightVector(), input * MoveCoeff);
	}
}
//-----------------------------

//ReplicationMouseInput--------
void AChel::MeshCompRepMulticast_Implementation(float RotationRoll)
{
	PoseableMeshComp->SetBoneRotationByName(TEXT("Bone_002"), { 0, 0, RotationRoll }, EBoneSpaces::ComponentSpace);
}


void AChel::MeshCompRepServer_Implementation(float RotationRoll)
{
	MeshCompRepMulticast(RotationRoll);
}

bool AChel::MeshCompRepServer_Validate(float RotationRoll)
{
	return true;
}
//-----------------------------

//MouseInput-------------------
void AChel::LookUp(float input)
{
	if (input != 0.0f && IsEnableInput)
	{
		input *= Sensetivity;
		float RotationRoll = PoseableMeshComp->GetBoneRotationByName(TEXT("Bone_002"), EBoneSpaces::ComponentSpace).Roll;
		if (RotationRoll + input >= 0.f && RotationRoll + input <= 179.f) {
			RotationRoll += input;
		}
		else if (RotationRoll + input > 179.f) {
			RotationRoll = 179.f;
		}
		else
			RotationRoll = 0;
		MeshCompRepServer(RotationRoll);
	}
}


void AChel::LookRight(float input)
{
	if (input != 0.0f && IsEnableInput) {
		input *= Sensetivity;
		AddControllerYawInput(input);
	}
}
//-----------------------------

//Jump-------------------------
void AChel::MyJump()
{
	Jump();
}
//-----------------------------


//Sprint-----------------------
void AChel::StartSprint() {
	GetCharacterMovement()->MaxWalkSpeed = 1200.f;
}

void AChel::StopSprint() {
	GetCharacterMovement()->MaxWalkSpeed = 800.f;
}
//-----------------------------


//KillFeed --------------------
void AChel::ShowKillFeed()
{
	KillFeed->SetVisibility(ESlateVisibility::Visible);
}

void AChel::UnShowKillFeed()
{
	KillFeed->SetVisibility(ESlateVisibility::Hidden);
}

//PlayStartingAnimation---------------------
void AChel::PlaySpawnAnimationSleep_Implementation() {
	UserView->PlayAnimation(UserView->Shading);
	SetActorEnableCollision(false);
}

//PlayStartingAnimation---------------------
void AChel::PlaySpawnAnimationAwake_Implementation() {
	UserView->PlayAnimation(UserView->Shading, 0, 1, EUMGSequencePlayMode::Type::Reverse);
	SetActorEnableCollision(true);
}

//-----------------------------
void AChel::PickUp() {
	if (ItemCodePickUp != -1) {
		switch (ItemCodePickUp) {
		case Boltorez:
		{
			UserView->WS_Boltorez->SetActiveWidgetIndex(1);
			break;
		}
		case KeyShelter:
		{
			UserView->WS_KeyShelter->SetActiveWidgetIndex(1);
			break;
		}
		case Otvertka:
		{
			UserView->WS_Otvertka->SetActiveWidgetIndex(1);
			break;
		}
		}
		DoesHave_Owner = true;
		NewHaveItemServer(ItemCodePickUp);
	}
}


void AChel::NewHaveItemServer_Implementation(int32 ItemType)
{
	DoesHave[ItemType] = true;
	TArray<AActor*>Players;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AChel::StaticClass(), Players);
	for (auto Player:Players)
		Cast<AChel>(Player)->NewHaveItemClient(ItemType);

	FHitResult OutHit;

	FVector StartLocation = CameraComp->GetComponentLocation();
	FVector EndLocation = StartLocation + CameraComp->GetForwardVector() * 300;

	FCollisionQueryParams CollisionParams;

	World->LineTraceSingleByChannel(OutHit, StartLocation, EndLocation, ECC_Visibility, CollisionParams);
	if (OutHit.GetActor()) {
		APickableItem* TempItem = Cast<APickableItem>(OutHit.GetActor());
		if (TempItem)
		{
			TempItem->Destroy();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Final Server LineTrace to Spectator"))
		}
	}
	
}

bool AChel::NewHaveItemServer_Validate(int32 ItemType)
{
	return true;
}

void AChel::NewHaveItemClient_Implementation(int32 ItemType)
{
	if (!DoesHave_Owner)
		switch (ItemType) {
		case Boltorez:
		{
			UserView->WS_Boltorez->SetRenderOpacity(0.5f);
			break;
		}
		case KeyShelter:
		{
			UserView->WS_KeyShelter->SetRenderOpacity(0.5f);
			break;
		}
		case Otvertka:
		{
			UserView->WS_Otvertka->SetRenderOpacity(0.5f);
			break;
		}
		default:
			break;
		}
	DoesHave_Owner = false;
}

void AChel::AddHitMarker_Implementation()
{
	UserView->Marker->SetVisibility(ESlateVisibility::Visible);
	FTimerHandle FuzeTimerHandle;
	World->GetTimerManager().SetTimer(FuzeTimerHandle, this, &AChel::RemoveHitMarker, 0.05, false);
}

void AChel::RemoveHitMarker()
{
	UserView->Marker->SetVisibility(ESlateVisibility::Hidden);
}

void AChel::StoneAttack(int StoneIndex)
{
	if (IsInGame) 
	{
		if (STONE_DAMAGE + Health + DeltaRadiation >= 1.0f)
		{
			KillerIndex = StoneIndex;
		}

		Health += STONE_DAMAGE;

		if (Health >= 1.0f)
		{

			if (DoesHave[Boltorez])
				GS->CurrentBoltorez--;
			if (DoesHave[KeyShelter])
				GS->CurrentKeyShelter--;
			if (DoesHave[Otvertka])
				GS->CurrentOtvertka--;

			TArray<AActor*>Players;
			UGameplayStatics::GetAllActorsOfClass(World, StaticClass(), Players);
			for (auto Player : Players)
					Cast<AChel>(Player)->RefreshWidgets(DoesHave, KillerIndex, Index, false);
			DoesHave.Init(false, 3);
			KillPlayer();
		}
	}
}

void AChel::RefreshWidgets_Implementation(const TArray<bool>& whatToUpdate, int KillerNickIndex, int VictimNickIndex, bool isSuicide)
{
	if (whatToUpdate[Boltorez])
	{
		UserView->WS_Boltorez->SetActiveWidgetIndex(0);
		UserView->WS_Boltorez->SetRenderOpacity(1.f);
	}
	if (whatToUpdate[Otvertka])
	{
		UserView->WS_Otvertka->SetActiveWidgetIndex(0);
		UserView->WS_Otvertka->SetRenderOpacity(1.f);
	}
	if (whatToUpdate[KeyShelter])
	{
		UserView->WS_KeyShelter->SetActiveWidgetIndex(0);
		UserView->WS_KeyShelter->SetRenderOpacity(1.f);
	}

	if (isSuicide) {
		UPlayerSuicide* PS_Widget = Cast<UPlayerSuicide>(CreateWidget(World, PlayerSuicide_class));
		PS_Widget->Player->SetText(GS->NickNames[VictimNickIndex]);
		UserView->VB_KillFeed->AddChild(PS_Widget);
	}
	else
	{
		UPlayerKillPlayer* PKP_Widget = Cast<UPlayerKillPlayer>(CreateWidget(World, PlayerKillPlayer_class));
		PKP_Widget->Killer->SetText(GS->NickNames[KillerNickIndex]);
		PKP_Widget->Victim->SetText(GS->NickNames[VictimNickIndex]);
		UserView->VB_KillFeed->AddChild(PKP_Widget);
	}

	if (whatToUpdate[Boltorez] || whatToUpdate[Otvertka] || whatToUpdate[KeyShelter])
	{
		UPlayerLostItem* PLI_Widget = Cast<UPlayerLostItem>(CreateWidget(World, PlayerLostItem_class));
		PLI_Widget->Player->SetText(GS->NickNames[VictimNickIndex]);
		if (whatToUpdate[Boltorez])
			PLI_Widget->IMG_Boltorez->SetVisibility(ESlateVisibility::Visible);
		if (whatToUpdate[Otvertka])
			PLI_Widget->IMG_Otvertka->SetVisibility(ESlateVisibility::Visible);
		if (whatToUpdate[KeyShelter])
			PLI_Widget->IMG_KeyShelter->SetVisibility(ESlateVisibility::Visible);

		UserView->VB_KillFeed->AddChild(PLI_Widget);
	}

}

void AChel::KillPlayer()
{
	GS->Deaths[Index] = FText::AsNumber(++Death);
	TArray<AActor*>Players;
	UGameplayStatics::GetAllActorsOfClass(World, AChel::StaticClass(), Players);
	for (auto Player : Players)
	{
		AChel* Chel = Cast<AChel>(Player);
		if (Chel->Index == KillerIndex)
		{
			GS->Kills[KillerIndex] = FText::AsNumber(++(Chel->Kills));
			break;
		}
	}
	DisableCollisionEverywhere();
	SetActorHiddenInGame(true);
	IsInGame = false;
	PlaySpawnAnimationSleep();
	IsEnableInput = false;
	FTimerHandle TimerHandle;
	World->GetTimerManager().SetTimer(TimerHandle, this, &AChel::SpawnPlayer, SPAWN_TIME, false);

	TArray<AActor*> WebCamSpectators;
	UGameplayStatics::GetAllActorsOfClassWithTag(World, ATargetPoint::StaticClass(), FName("WebCam"), WebCamSpectators);
	FTransform NewTrans = WebCamSpectators[FMath::Rand() % WebCamSpectators.Num()]->GetActorTransform();
	FActorSpawnParameters SpawnParams;
	AWebCamSpectator* WebSpec = World->SpawnActor<AWebCamSpectator>(WebCamSpectatorClass, NewTrans, SpawnParams);
	WebSpec->Index = Index;
	GetController()->Possess(WebSpec);
}

void AChel::SpawnPlayer()
{
	EnableCollisionEverywhere();
	SetActorHiddenInGame(false);
	IsEnableInput = true;
	IsInGame = true;
	Health = 0;
	Ammo = 10;

	TArray<AActor*> TargetPoints;
	UGameplayStatics::GetAllActorsOfClassWithTag(World, ATargetPoint::StaticClass(), TEXT("spawn"), TargetPoints);
	SetActorLocation(TargetPoints[FMath::Rand() % 4]->GetActorLocation());

	PlaySpawnAnimationAwake();
}

void AChel::DisableCollisionEverywhere_Implementation()
{
	SetActorEnableCollision(false);
}

void AChel::EnableCollisionEverywhere_Implementation()
{
	SetActorEnableCollision(true);
}

void AChel::PlayerOpenAreaUpdate_Implementation(int32 EscapeWay)
{
	TArray<AActor*>Players;
	UGameplayStatics::GetAllActorsOfClass(World, AChel::StaticClass(), Players);
	for (auto Player : Players) {
		AChel* Chel = Cast<AChel>(Player);
		Chel->RefreshWidgets_Winner(EscapeWay);
	}

	TArray<AActor*>Chels;
	GS->Areas[EscapeWay]->GetOverlappingActors(Chels);
	for (auto Player : Chels)
	{
		Cast<AChel>(Player)->ExitAvaliableUpdate(EscapeWay);
	}
}

bool AChel::PlayerOpenAreaUpdate_Validate(int32 EscapeWay)
{
	return true;
}

void AChel::RefreshWidgets_Winner_Implementation(int32 EscapeWay)
{
	switch (EscapeWay)
	{
	case Boltorez:
	{
		UserView->WS_Boltorez->SetVisibility(ESlateVisibility::Hidden);
		break;
	}
	case Otvertka:
	{
		UserView->WS_Otvertka->SetVisibility(ESlateVisibility::Hidden);
		break;
	}
	case KeyShelter:
	{
		UserView->WS_KeyShelter->SetVisibility(ESlateVisibility::Hidden);
		break;
	}
	}
}

void AChel::StuffAvaliableUpdate_Implementation(int32 EscapeWay)
{
	GS->AreaAvaliables[EscapeWay] = true;
}

bool AChel::StuffAvaliableUpdate_Validate(int32 EscapeWay)
{
	return true;
}

void AChel::ExitAvaliableUpdate_Implementation(int32 EscapeWay)
{
	UserView->EscapeText->SetVisibility(ESlateVisibility::Visible);
}

void AChel::PlayerEscape_Implementation(int32 EscapeWay)
{
	GS->AreaClosed[EscapeWay] = true;
	GS->Winners[EscapeWay] = GS->NickNames[Index];
	GS->EscapeTime[EscapeWay] = GS->CurrentTime;

	if (GS->GeneralLayer == 2) {
		TArray<AActor*>PlayerControllers;
		TArray<AActor*>Players;
		TArray<AActor*>Spectators;

		UGameplayStatics::GetAllActorsOfClass(World, ABP_PlayerController::StaticClass(), PlayerControllers);
		UGameplayStatics::GetAllActorsOfClass(World, AChel::StaticClass(), Players);
		UGameplayStatics::GetAllActorsOfClass(World, ASpectator::StaticClass(), Spectators);

		for (auto PlController : PlayerControllers)
		{
			Cast<ABP_PlayerController>(PlController)->AddFinalMenu();
		}

		for (auto Player : Players) {
			Cast<AChel>(Player)->DeleteGameHUD();
			Player->Destroy();
		}

		for (auto Spec : Spectators) {
			Spec->Destroy();
		}
	}
	else
	{
		TArray<AActor*>Chels;
		GS->Areas[EscapeWay]->GetOverlappingActors(Chels);
		for (auto Player : Chels)
		{
			Cast<AChel>(Player)->AreaClosedUpdate(EscapeWay);
		}

		PossessToSpectator();
	}
}

bool AChel::PlayerEscape_Validate(int32 EscapeWay)
{
	return true;
}

void AChel::AreaClosedUpdate_Implementation(int32 EscapeWay)
{
	AreaCode = -1;
	UserView->EscapeText->SetVisibility(ESlateVisibility::Hidden);
}


void AChel::PossessToSpectator()
{
	int iteration = 0;
	for (iteration = 0; iteration < 8; iteration += 2)
	{
		if (GS->Spectators[iteration]->Index == Index)
		{
			if (GS->Spectators[iteration]->IsPawnControlled())
				GS->Spectators[iteration]->UpdateSpectating_Right();
			if (GS->Spectators[iteration + 1]->IsPawnControlled())
				GS->Spectators[iteration + 1]->UpdateSpectating_Right();

			GS->Spectators[iteration]->IsKilled = true;
			GS->Spectators[iteration + 1]->IsKilled = true;
			break;
		}
	}

	iteration += 2;
	iteration += GS->GeneralLayer;
	GS->GeneralLayer++;
	while (true)
	{
		if (iteration >= 8)
		{
			iteration -= 8;
		}
		if (!GS->Spectators[iteration]->IsKilled)
		{
			GetController()->Possess(GS->Spectators[iteration]);
			Destroy();
			break;
		}
		iteration += 2;
	}
}


void AChel::DeleteGameHUD_Implementation()
{
	UserView->RemoveFromParent();
	UserView->Destruct();

	KillFeed->RemoveFromParent();
	KillFeed->Destruct();
	
	Destroy();
}