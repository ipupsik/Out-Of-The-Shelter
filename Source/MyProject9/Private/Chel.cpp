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
#include "CoreItem.h"
#include "Weapon_Character.h"
#include "ConsumableAbility.h"
#include "InteractiveItem.h"
#include "Weapon_Level.h"
#include "QAbility.h"
#include "PromptCollisionArea.h"
#include "QAbilityItem.h"
#include "Ventil.h"
#include "Consumable.h"
#include "InteractiveCache.h"
#include "AreaCollision.h"

// Sets default values
AChel::AChel()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PoseableMeshComp = CreateDefaultSubobject<UPoseableMeshComponent>(TEXT("PoseableMeshComp"));
	PoseableMeshComp->SetupAttachment(RootComponent);

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	Scene->SetupAttachment(PoseableMeshComp, TEXT("Bone_002_end"));

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(Scene);

	DamageCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("DamageCollision"));
	DamageCollision->SetupAttachment(RootComponent);

	SenseCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SenseCollision"));
	SenseCollision->SetupAttachment(RootComponent);

	WeaponPosition = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponPosition"));
	WeaponPosition->SetupAttachment(CameraComp);


	TimeLine_FOV_WebCam = CreateDefaultSubobject<UTimelineComponent>(TEXT("FOV_WebCam"));
	InterpFunction_FOV_WebCam.BindUFunction(this, FName("TimelineFloatReturn_FOV_WebCam"));

	IsAlreadyCreated = false;
	LastRAbilityIndex = -1;
	DoesNotImmortal = 1;
	CurrentStoneDamageBuffTempCount = 0;
	StoneDamageBuffTempValue = 1.0f;
	SpeedBustValue = 0;
	DoesRadiationAntidot = 1;
	StoneDamageBuffCount = 0;
	AmountBottleEffects = 0;
	ShieldsCount = 0;
	Health = 0;
	bIsAlreadyThrowing = false;
	IsInGame = false;
	Ammo = MaxAmmoCount;
	bLineTrace_is_need_refresh = false;
	DoesHave_Owner = false;
	IsNotInWebCam = true;
	CanThrowStone = true;
	CanFireWeapon = true;
	WebCamIterator = -1;
	IsNowInvisible = false;
	DoubleArmThrowing = false;
	bIsAlreadyThrowingLeft = false;
	CanalizationDamage = 1.0f;
	QAbilityType = -1;
	KillerIndex = -1;
	IsSuccessOpening = false;
	AreaCode = -1;
	bCanPossessWebCam = false;
	bCanWalkingAndWatching = true;
	IsAwake = true;
	Index = -1;
	InverseCoeff = 1.f;
	bInEscMenu = false;
	bInShopMenu = false;
	HaveSpecialAmmo = false;
	TempAntiDotEffect = 1.0f;
	ArmoryZelieEffect = 1.0f;
	AmountDetails = 5;
//	OpenAreaObj = nullptr;
	TickEnableGeneratorWidget = false;
	ProjectileDamageEffect = 1.0f;
	KeysCount.Init(0, 3);
	TargetItemsStatic.Init(nullptr, 0);
	TargetArrowsStatic.Init(nullptr, 0);
	TargetArrowsDynamic.Init(nullptr, 0);
	TargetItemsDynamic.Init(nullptr, 0);
	RAbilityPanel.Init(nullptr, 3);
	MyKDA_Stat.Init(nullptr, 4);
	CurrentWeapons.Init(nullptr, 2);
	IsRentgenRender = false;
}

//SetupReplicationVariables----
void AChel::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AChel, Index);
	DOREPLIFETIME(AChel, Health);
	DOREPLIFETIME(AChel, NickName);
	DOREPLIFETIME(AChel, Ammo);
	DOREPLIFETIME(AChel, DoesHave);
	DOREPLIFETIME(AChel, IsInGame);
}
//-----------------------------

void AChel::EnableChelDetector()
{
	for (auto& it : PlayersArray)
	{
		if (!it->IsPlayerOwner) {
			UE_LOG(LogTemp, Warning, TEXT("lla"));
			it->PoseableMeshComp->SetRenderCustomDepth(true);
			it->PoseableMeshComp->MarkRenderStateDirty();
		}
	}
}

void AChel::DisableChelDetector()
{
	for (auto& it : PlayersArray)
	{
		if (!it->IsPlayerOwner) {
			it->PoseableMeshComp->SetRenderCustomDepth(false);
			it->PoseableMeshComp->MarkRenderStateDirty();
		}
	}
}

void AChel::QAbilityEnable()
{
	if (CurQAbility)
	{
		if (CurQAbility->UseAbilityClient(this))
			CurQAbility->UseAbilityServer(this);
	}
}

void AChel::QAbilityDisable()
{
	if (CurQAbility)
	{
		if (CurQAbility->DeUseAbilityClient(this))
			CurQAbility->DeUseAbilityServer(this);
	}
}

void AChel::RAbilityEnable_Client()
{
	if (LastRAbilityIndex != -1 && !bInShopMenu && !bInEscMenu && bCanWalkingAndWatching && IsInGame)
	{
		if (RAbilityPanel[RAbilityTypeIndex]->UseAbilityClient(this))
			RAbilityEnable_Server(RAbilityPanel[RAbilityTypeIndex]->GetClass());
		UseRAbility();
	}
}

void AChel::RAbilityEnable_Server_Implementation(const UClass* Ability_class)
{
	UConsumableAbility* NewItem = NewObject<UConsumableAbility>(this, Ability_class);
	Cast<UConsumableAbility>(NewItem)->UseAbilityServer(this);
}

bool AChel::RAbilityEnable_Server_Validate(const UClass* Ability_class)
{
	return true;
}

void AChel::RAbility_HealPacket_Implementation()
{
	Health = 0;
}

bool AChel::RAbility_HealPacket_Validate()
{
	return true;
}

// Called when the game starts or when spawned
void AChel::BeginPlay()
{
	Super::BeginPlay();

	if (GetLocalRole() != ROLE_Authority)
		MyBeginPlay();
}

void AChel::MyBeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("StartPlaying"));
	GS = Cast<AGS>(GetWorld()->GetGameState());
	MyController = Cast<ABP_PlayerController>(GetController());
	IsServerAuth = GetLocalRole() == ROLE_Authority;
	IsPlayerOwner = UGameplayStatics::GetPlayerController(GetWorld(), 0) == MyController;
	World = GetWorld();
	GI = World->GetGameInstance<UGI>();
	
	Cast<AChel>(UGameplayStatics::GetPlayerCharacter(World, 0))->PlayersArray.Add(this);

	if (vCurveFOV_WebCam)
	{
		TimeLine_FOV_WebCam->AddInterpFloat(vCurveFOV_WebCam, InterpFunction_FOV_WebCam);

		TimeLine_FOV_WebCam->SetLooping(false);
		TimeLine_FOV_WebCam->SetIgnoreTimeDilation(true);
	}

	if (IsServerAuth) {
		TArray<AActor*>Players;
		UGameplayStatics::GetAllActorsOfClass(World, AChel::StaticClass(), Players);
		for (int i = 0; i < Players.Num(); i++)
		{
			bool CanUseIndex = true;
			for (auto& it : Players)
			{
				if (Cast<AChel>(it)->Index == i)
				{
					CanUseIndex = false;
					break;
				}
			}
			if (CanUseIndex)
			{
				Index = i;
				break;
			}
		}
		GS->AmountOfPlayers++;
		MyController->Index = Index;
		UE_LOG(LogTemp, Warning, TEXT("AmountOfPlayers increase Chel"))
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

	if (IsPlayerOwner) {
		UserView = Cast<UUserView>(CreateWidget(World, UserViewClass));
		VerstakViewWidget = Cast<UVerstakWidget>(CreateWidget(World, VerstakViewClass));
		GeneratorView = Cast<UGeneratorWidget>(CreateWidget(World, GeneratorView_class));
		KillFeed = Cast<UKillFeed>(CreateWidget(World, KillFeed_class));
		Widget_Note = Cast<UNoteWidget>(CreateWidget(World, NoteWidget_class));
		WebCamUI = Cast<UWebCamWidget>(CreateWidget(World, WebCamWidget_class));
		MyInventory = Cast<UInventory>(CreateWidget(World, Inventory_class));
		MyInventory->AddToViewport(2);
		MyController->TabWidget = Cast<UTab>(CreateWidget(World, Tab_Stat_class));
		MyController->TabWidget->AddToViewport(1);
		WebCamUI->AddToViewport();
		UserView->AddToViewport();
		KillFeed->AddToViewport();
		GeneratorView->AddToViewport();
		GeneratorView->SetVisibility(ESlateVisibility::Hidden);
		Widget_Note->AddToViewport();
		Widget_Note->SetVisibility(ESlateVisibility::Hidden);
		VerstakViewWidget->AddToViewport();
		VerstakViewWidget->WidgetOwner = this;
		VerstakViewWidget->SetVisibility(ESlateVisibility::Hidden);
		KillFeed->AddToViewport();

		UserView->Player = this;
		UserView->AmmoLabel->SetText(FText::AsNumber((int32)Ammo));

		TArray<AActor*>MainExis;
		UGameplayStatics::GetAllActorsOfClass(World, AItemPromtArrow_MainExis::StaticClass(), MainExis);
		for (auto& it : MainExis)
		{
			AItemPromtArrow_MainExis* Exis = Cast<AItemPromtArrow_MainExis>(it);
			switch (Exis->Type)
			{
			case 0:
			{
				MainExis_Canalizacia = Cast<AItemPromtArrow_MainExis>(it);
				UE_LOG(LogTemp, Warning, TEXT("AddCanalizacia"));
				break;
			}
			case 1:
			{
				MainExis_Shelter = Cast<AItemPromtArrow_MainExis>(it);
				UE_LOG(LogTemp, Warning, TEXT("AddArrowShelter"));
				break;
			}
			case 2:
			{
				MainExis_Ventilacia = Cast<AItemPromtArrow_MainExis>(it);
				UE_LOG(LogTemp, Warning, TEXT("AddArrowVentilacia"));
				break;
			}
			}
		}

		if (GI != nullptr) {
			Sensetivity = GI->Sensetivity;
			NickName = GI->NickName;
			IsAlreadyCreated = true;
			DeliverNicknameToServer(NickName);
		}
	}

	if (IsServerAuth && IsPlayerOwner)
	{
		MyController->IsHost = true;
		GS->MaxPlayersCount = GI->MaxPlayersCount;
	}

	//---------------------добавление начального камня ( у себя)-------------------------------------------------
	CreateWeapon(Stone_Class, 20, 0);
	//---------------------добавление начального камня End( у себя)-------------------------------------------------

	//---------------------обновление патронов у камня-------------------------------------------------
	GetAmmo_Server();
	//---------------------обновление патронов у камня-------------------------------------------------
}
void AChel::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	MyBeginPlay();
}

void AChel::ChangePBPosition(int32 TypeChange) {
	//GeneratorView->Corretca->SetValue(GeneratorView->PositionX[TypeChange]);
	GeneratorView->PB_Repair->SetPercent(GeneratorView->PositionX[TypeChange]);
	GeneratorView->Corretca->SetValue(0.0f);
	bToRight = true;
	GeneratorView->curSpeed = GeneratorView->Speed[TypeChange];
}

// Called every frame
void AChel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsInGame == true) {
		if (IsServerAuth) {
			Health += DeltaTime * 2 * 0.01f * RadCoeff * CanalizationDamage / 1.5f  * TempAntiDotEffect;
			if (Health > 1.0f) {
				TArray<AActor*>Players;
				UGameplayStatics::GetAllActorsOfClass(World, StaticClass(), Players);
				for (auto& it : Players)
				{
					if (KillerIndex != -1)
						Cast<AChel>(it)->RefreshWidgets(DoesHave, GS->NickNames[KillerIndex],
							GS->NickNames[Index], false);
					else
						Cast<AChel>(it)->RefreshWidgets(DoesHave, FText(),
							GS->NickNames[Index], false);
				}
				bCanWalkingAndWatching = true;
				if (IsNowInvisible)
					ReverceInvisibleEverywhere();
				KillPlayer();
				DoesHave.Init(false, 3);
				return;
			}
		}

		if (IsPlayerOwner) {
			//----------------------------------------------------для генератора Start--------------------------------------
			if (TickEnableGeneratorWidget) {
				if (bToRight) {
					GeneratorView->Corretca->SetValue(GeneratorView->Corretca->Value + (GeneratorView->curSpeed) * DeltaTime);
					//GeneratorView->PB_Repair->SetPercent(GeneratorView->PB_Repair->Percent + (GeneratorView->curSpeed) * DeltaTime);
					if (GeneratorView->Corretca->Value >= 1.0f) {
						bToRight = false;
					}
				}
				else {
					//GeneratorView->PB_Repair->SetPercent(GeneratorView->PB_Repair->Percent - (GeneratorView->curSpeed) * DeltaTime);
					GeneratorView->Corretca->SetValue(GeneratorView->Corretca->Value - (GeneratorView->curSpeed) * DeltaTime);
					if (GeneratorView->Corretca->Value <= 0.0f) {
						bToRight = true;
					}
				}
			}
			//----------------------------------------------------для генератора End--------------------------------------
			UserView->RadiationPoints->SetPercent(Health);
			UserView->DarkScreen->SetRenderOpacity(Health);

			FHitResult OutHit;

			FVector StartLocation = CameraComp->GetComponentLocation();
			FVector EndLocation = StartLocation + CameraComp->GetForwardVector() * 300;

			FCollisionQueryParams CollisionParams;

			if (World->LineTraceSingleByChannel(OutHit, StartLocation, EndLocation, ECC_Visibility, CollisionParams))
			{
				AInteractiveItem* TracedItem = Cast<AInteractiveItem>(OutHit.GetActor());
				if (TracedItem) { //Если мы стукнулись в нужный нам предмет
					if (LastInteractiveItem && LastInteractiveItem != TracedItem) {
						LastInteractiveItem->ToggleCustomDepth(false, this);
						if(!CurCoreArea)
							UserView->E_Mark->SetVisibility(ESlateVisibility::Hidden);
						if(GI->bIsEnabledPrompt)
							UserView->PropmptTextInterract->SetVisibility(ESlateVisibility::Hidden);
					}
					TracedItem->OnLineTraced(this);
					if (LastInteractiveItem != TracedItem) {
						LastInteractiveItem = TracedItem;
					}
				}
				else {
					if (LastInteractiveItem) {
						LastInteractiveItem->ToggleCustomDepth(false, this);
						LastInteractiveItem = nullptr;
						if(!CurCoreArea)
							UserView->E_Mark->SetVisibility(ESlateVisibility::Hidden);
						if(GI->bIsEnabledPrompt)
							UserView->PropmptTextInterract->SetVisibility(ESlateVisibility::Hidden);
					}
				}
			}
			else {
				if (LastInteractiveItem) {
					LastInteractiveItem->ToggleCustomDepth(false, this);
					LastInteractiveItem = nullptr;
					if(!CurCoreArea)
						UserView->E_Mark->SetVisibility(ESlateVisibility::Hidden);
					if(GI->bIsEnabledPrompt)
						UserView->PropmptTextInterract->SetVisibility(ESlateVisibility::Hidden);
				}
			}
		}
	}

	if (IsPlayerOwner) {
		for (int i = 0; i < TargetArrowsStatic.Num(); ++i)
		{
			UpdateTargetArrowPosition(TargetItemsStatic[i], TargetArrowsStatic[i]);
		}

		for (int i = 0; i < TargetArrowsDynamic.Num(); ++i)
		{
			UpdateTargetArrowPosition(TargetItemsDynamic[i], TargetArrowsDynamic[i]);
		}
	}
}

//NicknameSetup----------------
void AChel::DeliverNicknameToServer_Implementation(const FText& newNickName) {
	GS->NickNames[Index] = newNickName;
	NickName = newNickName;
	TArray<AActor*>Players;
	UGameplayStatics::GetAllActorsOfClass(World, AChel::StaticClass(), Players);
	for (auto& it : Players)
	{
		AChel* CurChel = Cast<AChel>(it);
		CurChel->CreateKDAWidget(Index, newNickName);
		if (CurChel->Index != Index) {
			CreateKDAWidget(CurChel->Index, CurChel->NickName);
			UE_LOG(LogTemp, Warning, TEXT("12354"))
		}
	}
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
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AChel::FireEvent);
	PlayerInputComponent->BindAction("WeaponSwitchUP", IE_Pressed, this, &AChel::WeaponSwitch);
	PlayerInputComponent->BindAction("WeaponSwitchDown", IE_Pressed, this, &AChel::WeaponSwitch);
	PlayerInputComponent->BindAction("FirstWeapon", IE_Pressed, this, &AChel::SwitchToFirstWeapon);
	PlayerInputComponent->BindAction("SpecialWeapon", IE_Pressed, this, &AChel::SwitchToSpecialWeapon);
	/*PlayerInputComponent->BindAction("ThrowStoneLeft", IE_Pressed, this, &AChel::ThrowStoneLeft);*/
	PlayerInputComponent->BindAction("PickUp", IE_Pressed, this, &AChel::PickUp);
	PlayerInputComponent->BindAction("PickUp", IE_Released, this, &AChel::PickUp_Released);
	PlayerInputComponent->BindAction("UpdateSpectating_Left", IE_Released, this, &AChel::UpdateSpectating_Left);
	PlayerInputComponent->BindAction("UpdateSpectating_Right", IE_Released, this, &AChel::UpdateSpectating_Right);
	PlayerInputComponent->BindAction("QAbility", IE_Pressed, this, &AChel::QAbilityEnable);
	PlayerInputComponent->BindAction("QAbility", IE_Released, this, &AChel::QAbilityDisable);
	PlayerInputComponent->BindAction("RAbility", IE_Pressed, this, &AChel::RAbilityEnable_Client);
}

void AChel::UpdateSpectating_Right()
{
	if (!IsNotInWebCam)
	{
		UpdateSpectating_Right_Server();
		CameraSwitch();
	}
}

void AChel::SetCameraRotationWebCam_Implementation(float RollRot, float PitchRot, float YawRot)
{
	BaseRotation = FRotator(PitchRot, YawRot, RollRot);
	UE_LOG(LogTemp, Warning, TEXT("TmpBaseRotationYaw - %f"  ),   YawRot);
	UE_LOG(LogTemp, Warning, TEXT("TmpBaseRotationPitch - %f"), PitchRot);
	CameraComp->SetWorldRotation(BaseRotation);
}

void AChel::UpdateSpectating_Right_Server_Implementation()
{
	WebCamIterator += 1;
	if (WebCamIterator >= GS->WebCams.Num())
	{
		WebCamIterator -= GS->WebCams.Num();
	}
	UE_LOG(LogTemp, Warning, TEXT("WebCamIterator - %d"), WebCamIterator);
	UE_LOG(LogTemp, Warning, TEXT("Count - %d"), GS->WebCams.Num());
	
	GoToWebCamServer(WebCamIterator);
	SetCameraRotationWebCam(GS->WebCams[WebCamIterator]->GetActorRotation().Roll,
		GS->WebCams[WebCamIterator]->GetActorRotation().Pitch,
		GS->WebCams[WebCamIterator]->GetActorRotation().Yaw);
}

bool AChel::UpdateSpectating_Right_Server_Validate()
{
	return true;
}

void AChel::UpdateSpectating_Left()
{
	if (!IsNotInWebCam)
	{
		UpdateSpectating_Left_Server();
		CameraSwitch();
	}
}

void AChel::UpdateSpectating_Left_Server_Implementation()
{
	WebCamIterator -= 1;
	if (WebCamIterator < 0)
	{
		WebCamIterator += GS->WebCams.Num();
	}
	UE_LOG(LogTemp, Warning, TEXT("WebCamIterator - %d"), WebCamIterator);
	UE_LOG(LogTemp, Warning, TEXT("Count - %d"), GS->WebCams.Num());

	GoToWebCamServer(WebCamIterator);
	SetCameraRotationWebCam(GS->WebCams[WebCamIterator]->GetActorRotation().Roll,
		GS->WebCams[WebCamIterator]->GetActorRotation().Pitch,
		GS->WebCams[WebCamIterator]->GetActorRotation().Yaw);
}

bool AChel::UpdateSpectating_Left_Server_Validate()
{
	return true;
}

void AChel::AddChromaticAbberationClient_Implementation()
{
	AddChromaticAbberation();
}

void AChel::TimelineFloatReturn_FOV_WebCam(float value)
{
	CameraComp->SetFieldOfView(value);
}

void AChel::FireEvent() {
	if (IsNotInWebCam && bCanWalkingAndWatching && !bInEscMenu && !bInShopMenu && CanFireWeapon && CurrentWeapons[CurrentIndex] && CurrentWeapons[CurrentIndex]->LeftAmmo > 0 ) {
		FireEvent_Server();
	}
}

void AChel::FireEvent_Server_Implementation() {
	CurrentWeapons[CurrentIndex]->Throw();
	if (CurrentIndex == 0) {
		TArray<AActor*> OverlappngActors;
		GetOverlappingActors(OverlappngActors, AAmmoPoint::StaticClass());
		for (auto& it : OverlappngActors) {
			AAmmoPoint* AmPt = Cast<AAmmoPoint>(it);
			if (AmPt) {
				AmPt->AmmoUpdate();
				break;
			}
		}
	}
}

bool AChel::FireEvent_Server_Validate() {
	return true;
}

void AChel::WeaponSwitch() {
	if (CurrentWeapons[(CurrentIndex + 1) % 2] && CurrentWeapons[(CurrentIndex + 1) % 2]->LeftAmmo > 0 && 
		IsNotInWebCam && !bInEscMenu && CanFireWeapon) {
		WeaponSwitch_Server((CurrentIndex + 1) % 2);
	}
}

void AChel::WeaponSwitch_Server_Implementation(int32 SlotIndex) {
	SetWeaponToSlotMulticast(SlotIndex);
}

bool AChel::WeaponSwitch_Server_Validate(int32 SlotIndex) {
	return true;
}

//KeyBoardInput----------------
void AChel::GoForward(float input) {
	if (bCanWalkingAndWatching && !bInEscMenu && !bInShopMenu) {
		if (input != 0.0f && IsNotInWebCam && CanThrowStone) {
			AddMovementInput(GetActorForwardVector(), input * MoveCoeff * InverseCoeff);
		}
	}
}

void AChel::GoRight(float input) {
	if (bCanWalkingAndWatching && !bInEscMenu && !bInShopMenu) {
		if (input != 0.0f && IsNotInWebCam && CanThrowStone) {
			AddMovementInput(GetActorRightVector(), input * MoveCoeff * InverseCoeff);
		}
	}
}
//-----------------------------

//ReplicationMouseInput--------
void AChel::MeshCompRepMulticast_Implementation(float RotationRoll)
{
	if (!IsPlayerOwner)
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
	if (bCanWalkingAndWatching && !bInEscMenu && !bInShopMenu) {
		if (IsNotInWebCam) {
			if (input != 0.0f)
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
				PoseableMeshComp->SetBoneRotationByName(TEXT("Bone_002"), { 0, 0, RotationRoll }, EBoneSpaces::ComponentSpace);
				MeshCompRepServer(RotationRoll);
			}
		}
		else
		{
			if (input != 0.0f) {
				input *= Sensetivity * WebCamSensetivity;
				float NewPitchRot = CameraComp->GetComponentRotation().Pitch - BaseRotation.Pitch;

				if (NewPitchRot + BaseRotation.Pitch >= 180.f)
					NewPitchRot -= 360;
				else if (NewPitchRot + BaseRotation.Pitch <= -180.f)
					NewPitchRot += 360;

				NewPitchRot = FMath::Clamp<float>(NewPitchRot + input, -MaxPitchAngle, MaxPitchAngle);
				UE_LOG(LogTemp, Warning, TEXT("Rotation - %f"), NewPitchRot + BaseRotation.Pitch);
				CameraComp->SetWorldRotation(FRotator(NewPitchRot + BaseRotation.Pitch,
					CameraComp->GetComponentRotation().Yaw, CameraComp->GetComponentRotation().Roll));
			}
		}
	}
}


void AChel::LookRight(float input)
{
	if (bCanWalkingAndWatching && !bInEscMenu && !bInShopMenu) {
		if (IsNotInWebCam) {
			if (input != 0.0f) {
				input *= Sensetivity;
				AddControllerYawInput(input);
			}
		}
		else
		{
			if (input != 0.0f) {
				input *= Sensetivity * WebCamSensetivity;
				float NewYawRot = CameraComp->GetComponentRotation().Yaw - BaseRotation.Yaw;

				NewYawRot = FMath::Clamp<float>(NewYawRot + input, -MaxYawAngle, MaxYawAngle);

				CameraComp->SetWorldRotation(FRotator(CameraComp->GetComponentRotation().Pitch, NewYawRot + BaseRotation.Yaw,
					CameraComp->GetComponentRotation().Roll));
			}
		}
	}
}
//-----------------------------

//Jump-------------------------
void AChel::MyJump()
{
	if (bCanWalkingAndWatching && !bInShopMenu && !bInEscMenu) {
		if (IsNotInWebCam)
			Jump();
	}
}
//-----------------------------


//Sprint-----------------------
void AChel::StartSprint_Server_Implementation()
{
	GetCharacterMovement()->MaxWalkSpeed = 1200.f + SpeedBustValue;
}

bool AChel::StartSprint_Server_Validate()
{
	return true;
}

void AChel::StartSprint() {
	GetCharacterMovement()->MaxWalkSpeed = 1200.f + SpeedBustValue;
	StartSprint_Server();
}

void AChel::StopSprint_Server_Implementation()
{
	GetCharacterMovement()->MaxWalkSpeed = 800.f + SpeedBustValue;
}

bool AChel::StopSprint_Server_Validate()
{
	return true;
}

void AChel::StopSprint() {
	GetCharacterMovement()->MaxWalkSpeed = 800.f + SpeedBustValue;
	StopSprint_Server();
}
//-----------------------------
//PlayStartingAnimation---------------------
void AChel::PlaySpawnAnimationSleep_Implementation() {
	for (int i = 0; i < TargetItemsStatic.Num(); ++i)
	{
		RemoveTargetArrowStatic(TargetItemsStatic[i]);
	}
	for (int i = 0; i < TargetArrowsDynamic.Num(); ++i)
	{
		RemoveTargetArrowDynamic(TargetArrowsDynamic[i]);
	}
	UserView->RadiationPoints->SetPercent(1.0f);
	UserView->DarkScreen->SetRenderOpacity(1.0f);
	ResetCacheKeys();
	if (bCanPossessWebCam)
		CanThrowStone = false;
	VerstakViewWidget->SetVisibility(ESlateVisibility::Hidden);
	Widget_Note->SetVisibility(ESlateVisibility::Hidden);
	SpawnDeadSound();
	UserView->PlayAnimation(UserView->Shading);
	AmountBottleEffects = 1;
	RemoveInvertMovement();

	if (LastInteractiveItem)
	{
		LastInteractiveItem->ToggleCustomDepth(false, this);
		LastInteractiveItem = nullptr;
		UserView->E_Mark->SetVisibility(ESlateVisibility::Hidden);
		if (GI->bIsEnabledPrompt)
			UserView->PropmptTextInterract->SetVisibility(ESlateVisibility::Hidden);
	}
	
	//na vsyakii
	MyController->bShowMouseCursor = false;
	MyController->SetInputMode(FInputModeGameOnly());

	FTimerHandle FuzeTimerHandle;
	World->GetTimerManager().SetTimer(FuzeTimerHandle, this, &AChel::SleepAnimation_End, 2.0f, false);
}

void AChel::SleepAnimation_End()
{
	bInShopMenu = false;
	bCanWalkingAndWatching = true;
	if (bCanPossessWebCam) {
		UserView->SetVisibility(ESlateVisibility::Hidden);
		IsNotInWebCam = false;
		UpdateSpectating_Right();
		WebCamUI->SetVisibility(ESlateVisibility::Visible);
		IsAwake = false;
	}
	else
	{
		IsAwake = false;
		MyController->PlayGameplayMusic();
	}
}

void AChel::AwakeAnimation_End()
{
	CameraComp->SetFieldOfView(90.0f);
	if (bCanPossessWebCam) {
		IsAwake = true;
	}
	else
	{
		bCanPossessWebCam = true;
		IsAwake = true;
	}
}

void AChel::CallEnableGasVent_Implementation() {
	AVentil* CurVent = Cast<AVentil>(LastInteractiveItem_Server);
	if(CurVent)
		CurVent->CreateGasOnLevel();
}
bool AChel::CallEnableGasVent_Validate() {
	return true;
}

//PlayStartingAnimation---------------------
void AChel::PlaySpawnAnimationAwake_Implementation() {
	TimeLine_FOV_WebCam->Stop();
	ShowNoiseWebCamUI(false);
	IsNotInWebCam = true;
	FTimerHandle FuzeTimerHandle;
	World->GetTimerManager().SetTimer(FuzeTimerHandle, this, &AChel::AwakeAnimation_End, 2, false);
	CanThrowStone = true;
	CameraComp->SetRelativeLocation({ 0,0,0 });
	CameraComp->SetRelativeRotation({ 0,0,0 });
	if (bCanPossessWebCam)
		CameraTurnOff();
	CameraComp->SetFieldOfView(90.0f);
	//StoneCountUpdate(MaxAmmoCount);

	WebCamUI->SetVisibility(ESlateVisibility::Hidden);

	UserView->SetVisibility(ESlateVisibility::Visible);
	SpawnWakeUpSound();
	UserView->PlayAnimation(UserView->Shading, 0, 1, EUMGSequencePlayMode::Type::Reverse);
}

//-----------------------------
void AChel::PickUp() {
	IsSuccessOpening = true;
	if (!bInEscMenu && !bInShopMenu) {
		if (IsNotInWebCam) {
			if (LastInteractiveItem)
			{
				if (LastInteractiveItem->PickUpEventClient(this))
					PickUp_Server();
			}
			else if (GenAreaObj)
				GenAreaObj->PressedEGenerator(this);
			else if (CurCoreArea)
				CurCoreArea->PressedEAreaCollision(this);
		}
		else
		{
			TimeLine_FOV_WebCam->Play();
			CameraZoomIn();
		}
	}
}

void AChel::PickUp_Released()
{
	IsSuccessOpening = false;
	if (bCanWalkingAndWatching && !bInEscMenu && !bInShopMenu) {
		if (IsNotInWebCam) {
			if (LastInteractiveItem)
			{
				if (LastInteractiveItem->PickUpEventReleaseClient(this))
					PickUp_Released_Server();
			}
			else if (CurCoreArea)
				UserView->StopAllAnimations();
		}
		else
		{
			TimeLine_FOV_WebCam->Reverse();
			CameraZoomOut();
		}
	}
}

void AChel::PickUp_Released_Server_Implementation() {
	FHitResult OutHit;

	FVector StartLocation = CameraComp->GetComponentLocation();
	FVector EndLocation = StartLocation + CameraComp->GetForwardVector() * 300;

	FCollisionQueryParams CollisionParams;

	World->LineTraceSingleByChannel(OutHit, StartLocation, EndLocation, ECC_Visibility, CollisionParams);
	if (OutHit.GetActor()) {
		AInteractiveItem* TracedItem = Cast<AInteractiveItem>(OutHit.GetActor());
		if (TracedItem)
		{
			TracedItem->PickUpEventReleaseServer(this);
		}
	}
}

bool  AChel::PickUp_Released_Server_Validate() {
	return true;
}

void AChel::ChangeIsAvaliableCache_Implementation()
{
	FHitResult OutHit;

	FVector StartLocation = CameraComp->GetComponentLocation();
	FVector EndLocation = StartLocation + CameraComp->GetForwardVector() * 300;

	FCollisionQueryParams CollisionParams;

	World->LineTraceSingleByChannel(OutHit, StartLocation, EndLocation, ECC_Visibility, CollisionParams);
	if (OutHit.GetActor()) {
		ACache* TempItem = Cast<ACache>(OutHit.GetActor());
		if (TempItem)
		{
			if (TempItem->IsEnabled) {
				TempItem->IsEnabled = false;
				TempItem->Opening();
			}
		}
	}
}

bool AChel::ChangeIsAvaliableCache_Validate()
{
	return true;
}

void AChel::PickUp_Server_Implementation()
{
	FHitResult OutHit;

	FVector StartLocation = CameraComp->GetComponentLocation();
	FVector EndLocation = StartLocation + CameraComp->GetForwardVector() * 300;

	FCollisionQueryParams CollisionParams;

	World->LineTraceSingleByChannel(OutHit, StartLocation, EndLocation, ECC_Visibility, CollisionParams);
	if (OutHit.GetActor()) {
		AInteractiveItem* TracedItem = Cast<AInteractiveItem>(OutHit.GetActor());
		
		LastInteractiveItem_Server = TracedItem;
		if (LastInteractiveItem_Server)
		{
			LastInteractiveItem_Server->PickUpEventServer(this);
		}
	}
}

bool AChel::PickUp_Server_Validate()
{
	return true;
}

void AChel::ReplaceRAbilityItem_Client(UClass* AbilityItemclass)
{
	ReplaceRAbilityItem_Server(RAbilityPanel[RAbilityTypeIndex]->GetClass());
	RAbilityPanel[RAbilityTypeIndex]->DestroyNonNativeProperties();
	RAbilityPanel[RAbilityTypeIndex] = NewObject<UConsumableAbility>(this, AbilityItemclass);
	RAbilityPanel[RAbilityTypeIndex]->UserViewSlot = Cast<URAbilitySlot>(MyInventory->RAbilityPanel->GetChildAt(RAbilityTypeIndex));
	RAbilityPanel[RAbilityTypeIndex]->SetAbilityToSlot();
	SetCurRAbilityUserView();
}

void AChel::ReplaceRAbilityItem_Server_Implementation(UClass* AbilityItemclass)
{
	FHitResult OutHit;

	FVector StartLocation = CameraComp->GetComponentLocation();
	FVector EndLocation = StartLocation + CameraComp->GetForwardVector() * 300;

	FCollisionQueryParams CollisionParams;

	World->LineTraceSingleByChannel(OutHit, StartLocation, EndLocation, ECC_Visibility, CollisionParams);
	if (OutHit.GetActor()) {
		AConsumable* TracedItem = Cast<AConsumable>(OutHit.GetActor());

		if (TracedItem)
		{
			FVector NewScale;
			FVector NewLocation;
			FRotator NewRotation;

			UConsumableAbility* CurRAbility = NewObject<UConsumableAbility>(this, AbilityItemclass);

			NewLocation = CurRAbility->GetCacheLocation(TracedItem->EnabledArrayIndex);
			NewScale = CurRAbility->GetCacheScale3D(TracedItem->EnabledArrayIndex);
			NewRotation = CurRAbility->GetCacheRotation(TracedItem->EnabledArrayIndex);

			AConsumable* NewItem = GetWorld()->SpawnActor<AConsumable>(CurRAbility->Consumable_class);
			FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
			NewItem->AttachToActor(GS->Caches[TracedItem->EnabledArrayIndex], AttachmentRules);
			NewItem->SetActorScale3D(NewScale);
			NewItem->AddActorLocalOffset(NewLocation);
			NewItem->AddActorLocalRotation(NewRotation);
			Cast<ACollectableItem>(NewItem)->EnabledArrayIndex = TracedItem->EnabledArrayIndex;
			GS->CacheItems_Stuff_IsAvaliable[TracedItem->EnabledArrayIndex] = false;

			TracedItem->Destroy();
		}
	}
}

bool AChel::ReplaceRAbilityItem_Server_Validate(UClass* AbilityItemclass)
{
	return true;
}

void AChel::ReplaceQAbilityItem(UClass* AbilityItemclass, int32 ItemIndex)
{
	FVector NewScale;
	FVector NewLocation;
	FRotator NewRotation;

	NewLocation = CurQAbility->GetCacheLocation(ItemIndex);
	NewScale = CurQAbility->GetCacheScale3D(ItemIndex);
	NewRotation = CurQAbility->GetCacheRotation(ItemIndex);
	CurQAbility->ConditionalBeginDestroy();
	CurQAbility = nullptr;
	
	
	AActor* NewItem = GetWorld()->SpawnActor<AActor>(AbilityItemclass);
	FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
	NewItem->AttachToActor(GS->Caches[ItemIndex], AttachmentRules);
	NewItem->SetActorScale3D(NewScale);
	NewItem->AddActorLocalOffset(NewLocation);
	NewItem->AddActorLocalRotation(NewRotation);
	Cast<ACollectableItem>(NewItem)->EnabledArrayIndex = ItemIndex;
	GS->CacheItems_Stuff_IsAvaliable[ItemIndex] = false;
}

void AChel::NewHaveItemClient_Implementation(int32 ItemType)
{
	
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

void AChel::RefreshWidgets_Implementation(const TArray<bool>& whatToUpdate, const FText& KillerNickName, 
	const FText& VictimNickName, bool IsEscape)
{
	UE_LOG(LogTemp, Warning, TEXT("WidgetUpdates"))
	if (whatToUpdate[0])
	{
		UserView->WS_Boltorez->SetActiveWidgetIndex(0);
	}
	if (whatToUpdate[2])
	{
		UserView->WS_Otvertka->SetActiveWidgetIndex(0);
	}
	if (whatToUpdate[1])
	{
		UserView->WS_KeyShelter->SetActiveWidgetIndex(0);
	}
	if (!IsEscape) {
		if (KillerNickName.ToString() == "") {
			UPlayerSuicide* PS_Widget = Cast<UPlayerSuicide>(CreateWidget(World, PlayerSuicide_class));
			PS_Widget->Player->SetText(VictimNickName);
			KillFeed->VB_KillFeed->AddChild(PS_Widget);
		}
		else
		{
			UPlayerKillPlayer* PKP_Widget = Cast<UPlayerKillPlayer>(CreateWidget(World, PlayerKillPlayer_class));
			PKP_Widget->Killer->SetText(KillerNickName);
			PKP_Widget->Victim->SetText(KillerNickName);
			KillFeed->VB_KillFeed->AddChild(PKP_Widget);
		}
	}

	if (whatToUpdate[0] || whatToUpdate[1] || whatToUpdate[2])
	{
		UPlayerLostItem* PLI_Widget = Cast<UPlayerLostItem>(CreateWidget(World, PlayerLostItem_class));
		PLI_Widget->Player->SetText(VictimNickName);
		if (whatToUpdate[0])
			PLI_Widget->IMG_Boltorez->SetVisibility(ESlateVisibility::Visible);
		if (whatToUpdate[2])
			PLI_Widget->IMG_Otvertka->SetVisibility(ESlateVisibility::Visible);
		if (whatToUpdate[1])
			PLI_Widget->IMG_KeyShelter->SetVisibility(ESlateVisibility::Visible);

		KillFeed->VB_KillFeed->AddChild(PLI_Widget);
	}
}

void AChel::KillPlayer()
{
	TArray<AActor*>Players;
	UGameplayStatics::GetAllActorsOfClass(World, AChel::StaticClass(), Players);

	DropCoreItems();

	CurrentWeapons[0]->LeftAmmo = 0;
	ChangeAmmoClients(0, 0);
	if (CurrentWeapons[1]) {
		CurrentWeapons[1]->LeftAmmo = 0;
		ChangeAmmoClients(0, 1);
	}
	HideCurrentWeapon();
	

	for (auto& Player : Players)
	{
		AChel* Chel = Cast<AChel>(Player);
		if (Chel)
		{
			Chel->DeleteStrelkaBadOutline_Client(Index);
			Chel->RefreshTabWidget(Index, KillerIndex);
		}
	}
	GetCharacterMovement()->StopMovementImmediately();
	DisableCollisionEverywhere();
	HideCustomItems(true);
	SetActorHiddenInGame(true);
	IsInGame = false;
	PlaySpawnAnimationSleep();
	KillerIndex = -1;
	FTimerHandle TimerHandle;
	World->GetTimerManager().SetTimer(TimerHandle, this, &AChel::SpawnPlayer, SPAWN_TIME, false);
}

void AChel::HideCustomItems_Implementation(bool NewHide)
{
	for (auto& CustomItem : CustomizationChilds)
	{
		if (CustomItem)
			CustomItem->SetActorHiddenInGame(NewHide);
	}
}


void AChel::GoToWebCamServer(int32 Iterator)
{
	SetActorLocation(GS->WebCams[Iterator]->GetActorLocation());
	GS->WebCams[Iterator]->CurChelix = this;
	if (GS->WebCams[Iterator]->is_Enabled == true)
	{
		ShowNoiseWebCamUI(false);
	}
	else
	{
		ShowNoiseWebCamUI(true);
	}

	UE_LOG(LogTemp, Warning, TEXT("Staying on webcam"));
}

void AChel::SpawnPlayer()
{
	UE_LOG(LogTemp, Warning, TEXT("Setting camera from webcam to player"));

	HideCustomItems(false);
	EnableCollisionEverywhere();
	//ShowStoneMulticast();
	SetActorHiddenInGame(false);
	IsNotInWebCam = true;
	IsInGame = true;
	Health = 0;
	Ammo = MaxAmmoCount;

	CurrentWeapons[0]->LeftAmmo = CurrentWeapons[0]->MaxAmmo;
	ChangeAmmoClients(CurrentWeapons[0]->MaxAmmo, 0);
	SwitchToFreeWeapon_Multicast();

	TArray<AActor*> TargetPoints;
	UGameplayStatics::GetAllActorsOfClassWithTag(World, ATargetPoint::StaticClass(), TEXT("spawn"), TargetPoints);
	SetActorLocation(TargetPoints[FMath::Rand() % 4]->GetActorLocation());

	PlaySpawnAnimationAwake();
}

void AChel::DisableCollisionEverywhere_Implementation()
{
	SetActorEnableCollision(false);
	GetCharacterMovement()->GravityScale = 0;
	GetCharacterMovement()->StopMovementImmediately();
}

void AChel::EnableCollisionEverywhere_Implementation()
{
	SetActorEnableCollision(true);
	GetCharacterMovement()->GravityScale = 1.2f;
	GetCharacterMovement()->StopMovementImmediately();
	CameraComp->SetFieldOfView(90.0f);
	CameraComp->SetRelativeRotation({ 0,0,0 });
}

void AChel::PlayerOpenAreaUpdate_Implementation(int32 EscapeWay)
{
	TArray<AActor*>Players;
	UGameplayStatics::GetAllActorsOfClass(World, AChel::StaticClass(), Players);
	for (auto& Player : Players) {
		Cast<AChel>(Player)->RefreshWidgets_Winner(EscapeWay);
	}

	TArray<AActor*>Chels;
	GS->Areas[EscapeWay]->GetOverlappingActors(Chels);
	for (auto& Player : Chels)
	{
		Cast<AChel>(Player)->ExitAvaliableUpdate(EscapeWay);
	}
	if (EscapeWay == 1){
		TArray<AActor*>Chels2;
		GS->Areas[3]->GetOverlappingActors(Chels2);
		for (auto& Player : Chels2)
		{
			Cast<AChel>(Player)->ExitAvaliableUpdate(3);
		}
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
	case 0:
	{
		UserView->WS_Boltorez->SetVisibility(ESlateVisibility::Hidden);
		break;
	}
	case 1:
	{
		UserView->WS_Otvertka->SetVisibility(ESlateVisibility::Hidden);
		break;
	}
	case 2:
	{
		UserView->WS_KeyShelter->SetVisibility(ESlateVisibility::Hidden);
		break;
	}
	}
}

void AChel::StuffAvaliableUpdate_Implementation(int32 EscapeWay)
{
	GS->AreaAvaliables[EscapeWay] = true;
	DoesHave[EscapeWay] = false;
}

bool AChel::StuffAvaliableUpdate_Validate(int32 EscapeWay)
{
	return true;
}

void AChel::ExitAvaliableUpdate_Implementation(int32 EscapeWay)
{
	//AreaCode = EscapeWay; //хз нужно ли
	if (CurCoreArea) {
		if (EscapeWay != 1)
			UserView->E_Mark->SetVisibility(ESlateVisibility::Visible);
		else
			UserView->E_Mark->SetVisibility(ESlateVisibility::Hidden);
		UserView->PropmptTextArea->SetText(CurCoreArea->AreaOpenAndCanEscape);
	}
	//UserView->EscapeText->SetVisibility(ESlateVisibility::Visible);
}

void AChel::PlayerEscape_Implementation(int32 EscapeWay)
{
	GS->AreaClosed[EscapeWay] = true;
	GS->WinnersNickNames.Add(GS->NickNames[Index]);
	GS->WinnersIndex.Add(Index);
	GS->EscapeTime.Add(GS->CurrentTime);
	
	for (int i = 0; i < CustomizationChilds.Num(); ++i)
	{
		if (CustomizationChilds[i])
			CustomizationChilds[i]->Destroy();
	}
	
	DoesHave[EscapeWay] = false;
	TArray<AActor*>PlayersEscape;
	UGameplayStatics::GetAllActorsOfClass(World, AChel::StaticClass(), PlayersEscape);
	for (auto& Player : PlayersEscape) {
		AChel* TmpPlayer = Cast<AChel>(Player);
		TmpPlayer->ShowEscapeWidget(EscapeWay, GS->NickNames[TmpPlayer->Index]);
		TmpPlayer->RefreshWidgets(DoesHave, FText(), GS->NickNames[Index], true);
	}

	DeleteAllWeapons();
	DropCoreItems();

	if (GS->GeneralLayer == 2) {
		GS->SpawnCustomizationChels();

		TArray<AActor*>Players;
		UGameplayStatics::GetAllActorsOfClass(World, AChel::StaticClass(), Players);
		for (auto& Player : Players) {
			Cast<AChel>(Player)->DeleteGameHUD();
		}

		TArray<AActor*>PlayerControllers;
		TArray<AActor*>FinalMenuPlayers;

		UGameplayStatics::GetAllActorsOfClass(World, ABP_PlayerController::StaticClass(), PlayerControllers);
		UGameplayStatics::GetAllActorsOfClass(World, AFinalMenuPawn::StaticClass(), FinalMenuPlayers);

		for (int i = 0; i < 4; ++i)
		{
			ABP_PlayerController* PC = Cast<ABP_PlayerController>(PlayerControllers[i]);
			PC->Possess(Cast<APawn>(FinalMenuPlayers[i]));
			PC->AddFinalMenu();
		}

		TArray<AActor*>Spectators;
		UGameplayStatics::GetAllActorsOfClass(World, ASpectator::StaticClass(), Spectators);
		for (auto& Spec : Spectators) {
			Spec->Destroy();
		}
		for (auto& Player : Players) {
			Destroy();
		}
	}
	else
	{
		TArray<AActor*>Chels;
		GS->Areas[EscapeWay]->GetOverlappingActors(Chels);
		for (auto& Player : Chels)
		{
			Cast<AChel>(Player)->AreaClosedUpdate(EscapeWay);
		}
		if (EscapeWay == 1) {
			TArray<AActor*>Chels2;
			GS->Areas[3]->GetOverlappingActors(Chels2);
			for (auto& Player : Chels2)
			{
				Cast<AChel>(Player)->AreaClosedUpdate(3);
			}
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
	//AreaCode = -1;
	if(!LastInteractiveItem)
		UserView->E_Mark->SetVisibility(ESlateVisibility::Hidden);
	UserView->PropmptTextArea->SetText(CurCoreArea->AreaClose);
	//UserView->EscapeText->SetVisibility(ESlateVisibility::Hidden);
	CurCoreArea = nullptr;
}


void AChel::PossessToSpectator()
{
	MyController->DisableOutline();
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
			MyController->Possess(GS->Spectators[iteration]);
			Destroy();
			break;
		}
		iteration += 2;
	}
}

void AChel::ChangeGeneratorStas_Implementation()
{
	GenAreaObj->Stadiya++;
	GenAreaObj->ChangeSoundAmbientToWorking();
	GoodAttempGeneratorSound();
	if (GenAreaObj->Stadiya >= 3) {
		GenAreaObj->Stadiya = 0;
		for (auto& it : GenAreaObj->PromtCollisionTerminal)
		{
			it->bISAvaliable = true;
		}

		for (auto& it : GenAreaObj->PromtCollisionGenerator)
		{
			it->bISAvaliable = false;
		}

		TArray<AActor*>ChelixZero;
		GenAreaObj->ShelterCollision[0]->Collision->GetOverlappingActors(ChelixZero, AChel::StaticClass());
		for (auto& it : ChelixZero)
		{
			Cast<AChel>(it)->ShowUIAfterTerminalAndGenerator(1, true);
		}

		TArray<AActor*>ChelixOne;
		GenAreaObj->ShelterCollision[1]->Collision->GetOverlappingActors(ChelixOne, AChel::StaticClass());
		for (auto& it : ChelixOne)
		{
			Cast<AChel>(it)->ShowUIAfterTerminalAndGenerator(3, true);
		}
		

		GenAreaObj->DoSomethinkGen();
		GS->IsShelterAvaliable = true;
		TArray<AActor*> temp;
		UGameplayStatics::GetAllActorsOfClass(World, APromptCollisionArea::StaticClass(), temp);
		for (auto& it : temp) {
			APromptCollisionArea* CurAreaPromt = Cast<APromptCollisionArea>(it);
			if (CurAreaPromt)
			{
				if (CurAreaPromt->TypePromptCollision == 1)
				{
					CurAreaPromt->bISAvaliable = false;
					CurAreaPromt->SettingAvaliableFalse();
				}
			}
		}


		ShowRandomItem();

		TArray<AActor*> Players;
		GenAreaObj->GetOverlappingActors(Players, AChel::StaticClass());
		for (auto& it : Players) {
			Cast<AChel>(it)->HideWidgetStas();
			Cast<AChel>(it)->ChangePB_Client(0);
		}
		GS->EventSpawnNote();
	}
	else {
		TArray<AActor*> Players;
		GenAreaObj->GetOverlappingActors(Players, AChel::StaticClass());
		for (auto& it: Players) {
			Cast<AChel>(it)->ChangePB_Client(GenAreaObj->Stadiya);
		}
	}
}

bool AChel::ChangeGeneratorStas_Validate()
{
	return true;
}

void AChel::CallDoThomethinkArea_Implementation()
{
	Cast<AOpenArea>(LastInteractiveItem)->DoSomethink();
}
bool AChel::CallDoThomethinkArea_Validate()
{
	return true;
}
void AChel::DeleteGameHUD_Implementation()
{
	UserView->RemoveFromParent();
	UserView->Destruct();

	KillFeed->RemoveFromParent();
	KillFeed->Destruct();
	
	Destroy();
}

void AChel::AddDoubleRadiationWidget_Implementation()
{
	//UserView->AddDoubleRadiationEffect();
}

void AChel::DisableDoubleRadiationWidget_Implementation()
{
	//UserView->DisableDoubleRadiationEffect();
}

void AChel::ChangePB_Client_Implementation(int32 ValueV)
{
	ChangePBPosition(ValueV);
}

void AChel::HideWidgetStas_Implementation()
{
	if(GI->bIsEnabledPrompt)
		UserView->PropmptTextArea->SetText(GenAreaObj->PromptGenTextNotActive);
	GeneratorView->SetVisibility(ESlateVisibility::Hidden);
	UserView->E_Mark->SetVisibility(ESlateVisibility::Hidden);
	TickEnableGeneratorWidget = false;
}

void AChel::RefreshOutline()
{
	Cast<AChel>(UGameplayStatics::GetPlayerCharacter(World, 0))->RemoveTargetArrowDynamic();
	PoseableMeshComp->SetRenderCustomDepth(false);
	PoseableMeshComp->MarkRenderStateDirty();
}

void AChel::DeleteArrowDelayKeyShelter() {
	MainExis_Shelter->Mesh->SetRenderCustomDepth(false);
	MainExis_Shelter->Mesh->MarkRenderStateDirty();
}

void AChel::DeleteArrowDelayBoltorez() {
	MainExis_Canalizacia->Mesh->SetRenderCustomDepth(false);
	MainExis_Canalizacia->Mesh->MarkRenderStateDirty();
}

void AChel::DeleteArrowDelayOtvertka() {
	MainExis_Ventilacia->Mesh->SetRenderCustomDepth(false);
	MainExis_Ventilacia->Mesh->MarkRenderStateDirty();
}

void AChel::OutlineBad_Multicast_Implementation()
{
	PoseableMeshComp->SetRenderCustomDepth(true);
	PoseableMeshComp->MarkRenderStateDirty();
	
	if (!IsPlayerOwner)
		Cast<AChel>(UGameplayStatics::GetPlayerCharacter(World, 0))->AddTargetArrowDynamic(this);
	FTimerHandle FuzeTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(FuzeTimerHandle, this, &AChel::RefreshOutline, 7, false);
}


void AChel::OutlineBad_Server_Implementation()
{
	if (PoseableMeshComp->CustomDepthStencilValue != 1)
		OutlineBad_Multicast();
}

bool AChel::OutlineBad_Server_Validate()
{
	return true;
}

void AChel::ShowRandomItem_Implementation() {
	TArray<AActor*> ImportantItems;
	UGameplayStatics::GetAllActorsOfClass(World, ACoreItem::StaticClass(), ImportantItems);
	if (ImportantItems.Num() != 0)
	{
		LastOutlineItem = Cast<ACoreItem>(ImportantItems[FMath::Rand() % ImportantItems.Num()]);
		LastOutlineItem->ToggleCustomDepth(true, this);
		AddTargetArrowDynamic(LastOutlineItem);

		FTimerHandle FuzeTimerHandle;
		World->GetTimerManager().SetTimer(FuzeTimerHandle, this, &AChel::HideRandomItem, ShowRandomItem_TIME, false);

	}
}

void AChel::HideRandomItem() {
	if (LastOutlineItem) 
	{
		LastOutlineItem->ToggleCustomDepth(false, this);
		LastOutlineItem = nullptr;
		RemoveTargetArrowDynamic();
	}
}

void AChel::ShowNoiseWebCamUI_Implementation(bool DoesNoise)
{
	ShowNoiseBlueprint(DoesNoise);
}

void AChel::AddInvisibleServer_Implementation()
{
	InvisibleEverywhere();
}

bool AChel::AddInvisibleServer_Validate()
{
	return true;
}

void AChel::HideNoteWidget_Implementation()
{
	Widget_Note->SetVisibility(ESlateVisibility::Hidden);
	bCanWalkingAndWatching = true;
}

void AChel::RefreshGeneratorArea_Implementation()
{
	UserView->PropmptTextArea->SetText(GenAreaObj->PromptGenNotRepairing);
	UserView->E_Mark->SetVisibility(ESlateVisibility::Visible);
}

void AChel::AddNumToTerminalServer_Implementation(int32 ButtonType)
{
	UE_LOG(LogTemp, Warning, TEXT("%d"), ButtonType);
	GS->AddNumToTerminal(ButtonType);
}

bool AChel::AddNumToTerminalServer_Validate(int32 ButtonType)
{
	return true;
}

void AChel::DeleteLAstNumServer_Implementation()
{
	GS->DeleteLastNumber();
}

bool AChel::DeleteLAstNumServer_Validate()
{
	return true;
}

void AChel::CheckCodeServer_Implementation()
{
	GS->CheckCode(Index);
}

bool AChel::CheckCodeServer_Validate()
{
	return true;
}

void AChel::UpdateTargetArrowPosition(AActor* TargetObj, UTargetArrow* ArrowWidget) {
	if (ArrowWidget && TargetObj) {
		APlayerController* CurPC = UGameplayStatics::GetPlayerController(World, 0);
		//ScreenPosObj = PofigKakNaz(TargetObj);
		PofigKakNaz(TargetObj);
		//CurPC->ProjectWorldLocationToScreen(TargetObj->GetActorLocation(), ScreenPosObj, true);
		int32 ScreenWidth = 0;
		int32 ScreenHeight = 0;
		CurPC->GetViewportSize(ScreenWidth, ScreenHeight);
		

		FVector temp = UKismetMathLibrary::InverseTransformLocation(CameraComp->GetComponentTransform(), TargetObj->GetActorLocation());
		FRotator CurRotation = UKismetMathLibrary::MakeRotFromX(temp);
		//UE_LOG(LogTemp, Warning, TEXT("Screen width %d"), ScreenWidth);
		//UE_LOG(LogTemp, Warning, TEXT("Screen height %d"), ScreenHeight);
		//UE_LOG(LogTemp, Warning, TEXT("ScreenPosObj.X %f"), ScreenPosObj.X);
		//UE_LOG(LogTemp, Warning, TEXT("ScreenPosObj.Y %f"), ScreenPosObj.Y);
		//UE_LOG(LogTemp, Warning, TEXT("You looking at Actor!"));
		if (0 < int32(ScreenPosObj.X) && int32(ScreenPosObj.X) <= ScreenWidth && 0 < int32(ScreenPosObj.Y) && int32(ScreenPosObj.Y) <= ScreenHeight) 
		{ //в экране
			UE_LOG(LogTemp, Warning, TEXT("You looking at Actor!"));
			ArrowWidget->SetVisibility(ESlateVisibility::Hidden);
		}
		else 
		{ //не в экране
			ArrowWidget->SetVisibility(ESlateVisibility::Visible);
			ArrowWidget->SetRenderTransformAngle(0);
			FVector2D NewPos; //новая позиция стрелки на экране
			if (0 <= int32(ScreenPosObj.X) && int32(ScreenPosObj.X) <= ScreenWidth) 
			{ //сверху или снизу
				float ArrowNewPosX = UKismetMathLibrary::FClamp((CurRotation.Yaw + 45.f) * ScreenWidth / 90.f, ScreenWidth * 0.05, ScreenWidth * 0.95 - 80.f);
				NewPos.X = ArrowNewPosX;
				if (CurRotation.Pitch < 0) 
				{ //снизу
					NewPos.Y = ScreenHeight * 0.95 - 80;
					ArrowWidget->SetPositionInViewport(NewPos);
					ArrowWidget->SetRenderTransformAngle((CurRotation.Yaw * -1.f) + 180.f);
				}
				else 
				{ //сверху
					NewPos.Y = ScreenHeight * 0.05;
					ArrowWidget->SetPositionInViewport(NewPos);
					ArrowWidget->SetRenderTransformAngle(CurRotation.Yaw);
				}
			}
			else 
			{ //слева или справа
				float ArrowNewPosY = UKismetMathLibrary::FClamp((ScreenHeight / 2) -(((CurRotation.Pitch + 20.f) * ScreenHeight / 40.f) - (ScreenHeight/2)), ScreenHeight * 0.05, ScreenHeight * 0.95 - 80.f);
				NewPos.Y = ArrowNewPosY;
				if (CurRotation.Yaw > 0) 
				{ //справа
					NewPos.X = ScreenWidth * 0.95 - 80.f;
					ArrowWidget->SetPositionInViewport(NewPos);
					ArrowWidget->SetRenderTransformAngle((CurRotation.Pitch * -1.f) + 90.f);
				}
				else 
				{ //слева
					NewPos.X = ScreenWidth * 0.05;
					ArrowWidget->SetPositionInViewport(NewPos);
					ArrowWidget->SetRenderTransformAngle(CurRotation.Pitch - 90.f);
				}
			}
		}
	}
	else if (!TargetObj && ArrowWidget)
	{
		RemoveTargetArrowDynamic(ArrowWidget);
	}

}

void AChel::AddTargetArrowStatic(AActor * TargetObj)
{
	UTargetArrow* Arrow = Cast<UTargetArrow>(CreateWidget(World, TargetArrowClass));
	if (Arrow) 
	{
		Arrow->AddToViewport();
		TargetItemsStatic.Add(TargetObj);
		TargetArrowsStatic.Add(Arrow);
		PlayArrowSound();
	}
}

void AChel::RemoveTargetArrowStatic(AActor * TargetObj)
{
	for (int i = 0; i < TargetItemsStatic.Num(); ++i) 
	{
		if (TargetItemsStatic[i] == TargetObj) 
		{
			TargetArrowsStatic[i]->RemoveFromViewport();
			TargetItemsStatic.RemoveAt(i);
			TargetArrowsStatic.RemoveAt(i);
		}
	}
}

void AChel::AddTargetArrowDynamic(AActor * TargetObj)
{
	UTargetArrow* Arrow = Cast<UTargetArrow>(CreateWidget(World, TargetArrowClass));
	if (Arrow)
	{
		Arrow->AddToViewport();
		TargetItemsDynamic.Add(TargetObj);
		TargetArrowsDynamic.Add(Arrow);
		PlayArrowSound();
	}
}

void AChel::RemoveTargetArrowDynamic() 
{
	if (TargetItemsDynamic.Num() != 0) {
		TargetArrowsDynamic[0]->RemoveFromViewport();
		TargetItemsDynamic.RemoveAt(0);
		TargetArrowsDynamic.RemoveAt(0);
	}
}

void AChel::RemoveTargetArrowDynamic(UTargetArrow* ArrowObj)
{
	for (int i = 0; i < TargetArrowsDynamic.Num(); ++i)
	{
		if (TargetArrowsDynamic[i] == ArrowObj)
		{
			TargetArrowsDynamic[i]->RemoveFromParent();
			TargetArrowsDynamic.RemoveAt(i);
			TargetItemsDynamic.RemoveAt(i);
		}
	}
}

void AChel::DeleteStrelkaBadOutline_Client_Implementation(int32 ChelIndex)
{
	RemoveArrowBadOutline(ChelIndex);
}

void AChel::ShowEscapeWidget_Implementation(int32 Escape_Way, const FText& ThrowNickName)
{
	UPlayerEscapeWidget* TmpWidget = Cast<UPlayerEscapeWidget>(CreateWidget(World, PlayerEscapeWidget_class));
	TmpWidget->NickName->SetText(ThrowNickName);
	switch (Escape_Way)
	{
	case 0:
	{
		TmpWidget->BoltorezImage->SetVisibility(ESlateVisibility::Visible);
		TmpWidget->WayOut->SetText(FText::FromString("escaped from Canalizacia"));
		break;
	}
	case 1:
	{
		TmpWidget->KeyShelterImage->SetVisibility(ESlateVisibility::Visible);
		TmpWidget->WayOut->SetText(FText::FromString("escaped from Shelter Door"));
		break;
	}
	case 2:
	{
		TmpWidget->OtvertkaImage->SetVisibility(ESlateVisibility::Visible);
		TmpWidget->WayOut->SetText(FText::FromString("escaped from Ventilacia"));
		break;
	}
	}
	KillFeed->VB_KillFeed->AddChild(TmpWidget);
}

void AChel::RemoveArrowBadOutline(int32 ChelIndex)
{
	for (int i = 0; i < TargetItemsDynamic.Num(); ++i)
	{
		AChel* BadChel = Cast<AChel>(TargetItemsDynamic[i]);
		if (BadChel && BadChel->Index == ChelIndex)
		{
			TargetArrowsDynamic[i]->RemoveFromParent();
			TargetItemsDynamic.RemoveAt(i);
			TargetArrowsDynamic.RemoveAt(i);
		}
	}
}

void AChel::ShowUIAfterTerminalAndGenerator_Implementation(int32 NewAreaType, bool DoesEnabled)
{
	if (DoesEnabled) {
		//AreaCode = NewAreaType; //скорее всего не нужно
		//убираем стрелки с генератора и ставим на терминал
		TArray<AActor*> Govno;
		UGameplayStatics::GetAllActorsOfClass(World, AGeneratorArea::StaticClass(), Govno);
		AGeneratorArea* GNRTR = Cast<AGeneratorArea>(Govno[0]);
		for (int i = 0; i < 2; i++) {
			RemoveTargetArrowStatic(GNRTR->PromtCollisionGenerator[0]->PromptedItems[i]);
			GNRTR->PromtCollisionGenerator[0]->PromptedItems[i]->Mesh->SetRenderCustomDepth(false);
			GNRTR->PromtCollisionGenerator[0]->PromptedItems[i]->Mesh->MarkRenderStateDirty();
		}
		for (int i = 0; i < 1; i++) {
			AddTargetArrowStatic(GNRTR->PromtCollisionTerminal[0]->PromptedItems[i]);
			GNRTR->PromtCollisionTerminal[0]->PromptedItems[i]->Mesh->SetRenderCustomDepth(true);
			GNRTR->PromtCollisionTerminal[0]->PromptedItems[i]->Mesh->MarkRenderStateDirty();
		}
		if (NewAreaType <= 2 && !GS->AreaAvaliables[NewAreaType])
		{
			if (CurCoreArea) {
				if (DoesHave[NewAreaType]) {
					UserView->E_Mark->SetVisibility(ESlateVisibility::Visible);
					UserView->PropmptTextArea->SetText(CurCoreArea->AreaAvaliableAndCanOpen);
				}
				else
					UserView->PropmptTextArea->SetText(CurCoreArea->AreaAvaliableAndHaveNoItem);
			}	
				//UserView->HoldText->SetVisibility(ESlateVisibility::Visible);
		}
	}
	else
	{
		//AreaCode = -1; //скорее всего не нужно
		//убираем стрелки с терминала и ставим на генератор
		TArray<AActor*> Govno;
		UGameplayStatics::GetAllActorsOfClass(World, AGeneratorArea::StaticClass(), Govno);
		AGeneratorArea* GNRTR = Cast<AGeneratorArea>(Govno[0]);
		for (int i = 0; i < 1; i++) {
			RemoveTargetArrowStatic(GNRTR->PromtCollisionTerminal[0]->PromptedItems[i]);
			GNRTR->PromtCollisionTerminal[0]->PromptedItems[i]->Mesh->SetRenderCustomDepth(false);
			GNRTR->PromtCollisionTerminal[0]->PromptedItems[i]->Mesh->MarkRenderStateDirty();
		}
		for (int i = 0; i < 2; i++) {
			AddTargetArrowStatic(GNRTR->PromtCollisionGenerator[0]->PromptedItems[i]);
			GNRTR->PromtCollisionGenerator[0]->PromptedItems[i]->Mesh->SetRenderCustomDepth(true);
			GNRTR->PromtCollisionGenerator[0]->PromptedItems[i]->Mesh->MarkRenderStateDirty();
		}
		if (NewAreaType <= 2 && !GS->AreaAvaliables[NewAreaType])
		{
			if (DoesHave[NewAreaType]) { //на случай, если чел открывал дверь букера, но вырубили генератор
				IsSuccessOpening = false;
				UserView->StopAllAnimations();
			}
			if (!LastInteractiveItem) {
				UserView->E_Mark->SetVisibility(ESlateVisibility::Hidden);
			}
			if (CurCoreArea)
				UserView->PropmptTextArea->SetText(CurCoreArea->AreaNotAvaliable);
			//UserView->HoldText->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void AChel::ResetCacheKeys()
{
	DeleteArrowDelayKeyShelter();
	DeleteArrowDelayBoltorez();
	DeleteArrowDelayOtvertka();
	KeysCount[0] = 0;
	KeysCount[1] = 0;
	KeysCount[2] = 0;
	UserView->KeyLeft_Gold->SetText(FText::AsNumber(0));
	UserView->KeyLeft_Silver->SetText(FText::AsNumber(0));
	UserView->KeyLeft_Bronze->SetText(FText::AsNumber(0));
}

void AChel::StopUseSpeedBust()
{
	CurrentSpeedBustCount--;
	if (CurrentSpeedBustCount == 0)
	{
		SpeedBustValue = 0;
	}
}

void AChel::UseSpeedBust_Server_Implementation()
{
	SpeedBustValue = 300;
	GetCharacterMovement()->MaxWalkSpeed = 800.f + SpeedBustValue;
	CurrentSpeedBustCount++;
	FTimerHandle FuzeTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(FuzeTimerHandle, this, &AChel::StopUseSpeedBust, 20, false);
}

bool AChel::UseSpeedBust_Server_Validate()
{
	return true;
}

void AChel::AddImmortalServer_Implementation()
{
	DoesNotImmortal = 0;
	DoesNotImmortalCount++;
	FTimerHandle FuzeTimerHandle2;
	GetWorld()->GetTimerManager().SetTimer(FuzeTimerHandle2, this, &AChel::RemoveImmortalServer, 4, false);
}

bool AChel::AddImmortalServer_Validate()
{
	return true;
}

void AChel::RemoveImmortalServer()
{
	DoesNotImmortalCount--;
	if (DoesNotImmortalCount == 0)
	{
		DoesNotImmortal = 1;
	}
}

void AChel::CreateKDAWidget_Implementation(int32 PlayerIndex, const FText& newNickName)
{
	if (IsAlreadyCreated && newNickName.ToString() != "") {
		UKDA_Stat* NewKDAWidget = Cast<UKDA_Stat>(CreateWidget(World, KDA_Stat_class));
		NewKDAWidget->NickName->SetText(newNickName);
		NewKDAWidget->Deaths->SetText(FText::AsNumber(0));
		NewKDAWidget->Kills->SetText(FText::AsNumber(0));
		NewKDAWidget->PlayerIndex = PlayerIndex;

		MyController->TabWidget->Tab_KD_Stat->AddChild(NewKDAWidget);
		MyKDA_Stat[PlayerIndex] = NewKDAWidget;
	}
}

void AChel::RefreshTabWidget_Implementation(int32 VictimIndex, int32 newKillerIndex)
{
	for (int i = 0; i < 4; ++i)
	{
		if (MyKDA_Stat[i]) {
			if (MyKDA_Stat[i]->PlayerIndex == VictimIndex)
			{
				MyKDA_Stat[i]->DeathsCount++;
				MyKDA_Stat[i]->Deaths->SetText(FText::AsNumber(MyKDA_Stat[i]->DeathsCount));
			}

			if (MyKDA_Stat[i]->PlayerIndex == newKillerIndex)
			{
				MyKDA_Stat[i]->KillsCount++;
				MyKDA_Stat[i]->Kills->SetText(FText::AsNumber(MyKDA_Stat[i]->KillsCount));
			}
		}
	}
}

void AChel::DeleteKDATab_Implementation(int32 newPlayerIndex)
{
	for (int i = 0; i < 4; ++i)
	{
		if (MyKDA_Stat[i]) {
			if (MyKDA_Stat[i]->PlayerIndex == newPlayerIndex)
			{
				MyKDA_Stat[i]->RemoveFromParent();
			}
		}
	}
}

void AChel::ShowInventory()
{
	MyInventory->SetVisibility(ESlateVisibility::Visible);
}

void AChel::UnShowInventory()
{
	MyInventory->SetVisibility(ESlateVisibility::Hidden);
}

void AChel::UseRAbility()
{
	LastRAbilityIndex = RAbilityTypeIndex - 1;
	for (int i = RAbilityTypeIndex + 1; i < RAbilityPanel.Num(); i++)
	{
		if (RAbilityPanel[i])
		{
			UConsumableAbility* tmp = RAbilityPanel[i - 1];
			RAbilityPanel[i - 1] = RAbilityPanel[i];
			RAbilityPanel[i] = tmp;
			URAbilitySlot* tmpSlot = RAbilityPanel[i - 1]->UserViewSlot;
			RAbilityPanel[i - 1]->UserViewSlot = RAbilityPanel[i]->UserViewSlot;
			RAbilityPanel[i]->UserViewSlot = tmpSlot;
			RAbilityPanel[i - 1]->ResetAbility();
			LastRAbilityIndex++;
			if (i == RAbilityTypeIndex + 1)
			{
				RAbilityPanel[i - 1]->UserViewSlot->HoveredRAbility();
			}
		}
	}
	if (LastRAbilityIndex < RAbilityTypeIndex)
	{
		RAbilityTypeIndex = LastRAbilityIndex;
	}
	SetCurRAbilityUserView();
	RAbilityPanel[LastRAbilityIndex + 1]->UserViewSlot->SetVisibility(ESlateVisibility::Hidden);
	RAbilityPanel[LastRAbilityIndex + 1]->UserViewSlot->SelectImage->SetVisibility(ESlateVisibility::Hidden);
	RAbilityPanel[LastRAbilityIndex + 1] = nullptr;
}

bool AChel::NewRAbility(const UClass* Ability_class)
{
	if (LastRAbilityIndex == -1)
	{
		RAbilityTypeIndex = 0;
	}

	if (LastRAbilityIndex != 2)
	{
		LastRAbilityIndex++;
		RAbilityPanel[LastRAbilityIndex] = NewObject<UConsumableAbility>(this, Ability_class);
		RAbilityPanel[LastRAbilityIndex]->UserViewSlot = Cast<URAbilitySlot>(MyInventory->RAbilityPanel->GetChildAt(LastRAbilityIndex));
		RAbilityPanel[LastRAbilityIndex]->SetAbilityToSlot();
		if (LastRAbilityIndex == 0)
		{
			SetCurRAbilityUserView();
		}
		return true;
	}
	else
		return false;
}

void AChel::SetCurRAbilityUserView()
{
	if (LastRAbilityIndex != -1) {
		RAbilityPanel[RAbilityTypeIndex]->SetCurRAbilityUserView(this);
	}
	else
	{
		FSlateBrush NewBrush;
		NewBrush.SetResourceObject(DefaultRAbilityImage);
		UserView->CurRSlot->AbilityImage->SetBrush(NewBrush);
	}
}

void AChel::DropCoreItems()
{
	if (DoesHave[0]) {
		CreateDroppedItem(BoltorezClass_Dropped);
	}
	if (DoesHave[1]) {
		CreateDroppedItem(KeyClass_Dropped);
	}
	if (DoesHave[2]) {
		CreateDroppedItem(OtvertkaClass_Dropped);
	}
}
void AChel::CreateDroppedItem(UClass* DroppedItemClass) {
	FTransform Trsfrm;
	Trsfrm.SetLocation(DamageCollision->GetComponentLocation());
	Trsfrm.SetRotation(FQuat(FRotator(DamageCollision->GetComponentRotation())));
	Trsfrm.SetScale3D(FVector(1.0f, 1.0f, 1.0f));
	ACoreItem_Dropped* DroppedItm = World->SpawnActor<ACoreItem_Dropped>(DroppedItemClass, Trsfrm);
	DroppedItm->Mesh->SetPhysicsLinearVelocity(FVector(CameraComp->GetForwardVector() * 200.f));
}

//----------------оружия------------------------
void AChel::SwitchToFirstWeapon() {
	if (CurrentWeapons[0] && CurrentWeapons[0]->LeftAmmo > 0 &&
		IsNotInWebCam && !bInEscMenu && CanFireWeapon && CurrentIndex != 0) {
		WeaponSwitch_Server(0);
	}
}

void AChel::SwitchToSpecialWeapon() {
	if (CurrentWeapons[1] && CurrentWeapons[1]->LeftAmmo > 0 &&
		IsNotInWebCam && !bInEscMenu && CanFireWeapon && CurrentIndex != 1) {
		WeaponSwitch_Server(1);
	}
}

void AChel::CreateWeaponMulticast_Implementation(UClass* WeaponCreatedClass, int32 Amount, int32 IndexSlot) {
	CreateWeapon(WeaponCreatedClass, Amount, IndexSlot);
}

void AChel::CreateWeapon(UClass* WeaponCreatedClass, int32 Amount, int32 IndexSlot) {
	UE_LOG(LogTemp, Warning, TEXT("I`m in Multicast"));
	AChel* Player = nullptr;

	AWeapon_Character* CreatedWeapon = World->SpawnActor<AWeapon_Character>(WeaponCreatedClass);
	CreatedWeapon->WeaponOwner = this;
	CreatedWeapon->LeftAmmo = Amount;
	CreatedWeapon->MaxAmmo = CreatedWeapon->MaxAmmo + CreatedWeapon->ExtraAmountAmmo * HaveSpecialAmmo;

	FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
	CreatedWeapon->AttachToComponent(WeaponPosition, AttachmentRules);

	if (CurrentWeapons[IndexSlot])
		CurrentWeapons[IndexSlot]->Destroy();
	CurrentWeapons[IndexSlot] = CreatedWeapon;
	if (IndexSlot == 0) { //на случай, если устанавливаем камень
		SetWeaponToSlot(0);
	}
	else {
		if (CurrentIndex == 0 && CurrentWeapons[0]->LeftAmmo == 0 || CurrentIndex == 1) {
			SetWeaponToSlot(1);
		}
		else {
			CreatedWeapon->GunMesh->SetVisibility(false);
		}
	}
}

void AChel::SetWeaponToSlot(int32 IndexWeapon) //вызывается из мультикастового события
{
	CurrentWeapons[IndexWeapon]->GunMesh->SetVisibility(true);
	if(CurrentWeapons[(IndexWeapon + 1) % 2]) //условие нужно при старте игры, когда второго оружия нет
		CurrentWeapons[(IndexWeapon + 1) % 2]->GunMesh->SetVisibility(false);
	CurrentIndex = IndexWeapon;
	if (IsPlayerOwner) {
		RefreshWidgetAmmoOwning(CurrentWeapons[CurrentIndex]->LeftAmmo, CurrentWeapons[CurrentIndex]->MaxAmmo, CurrentIndex);
	}
}

void AChel::SwitchToFreeWeapon() {
	if (CurrentWeapons[0]->LeftAmmo == 0) {
		if (CurrentWeapons[1]){//если у нас валидно второе оружие
			if (CurrentWeapons[1]->LeftAmmo == 0) { //нет второго оружия и нет первого оружия
				CurrentIndex = 0;
				if (IsPlayerOwner) {
					ClearWeaponInfo();
				}
			}
			else { //нет первого оружия и есть второе оружие
				SetWeaponToSlot(1);
			}
		}
		else {//нет первого оружия и не валидно второе оружие
			CurrentIndex = 0;
			if (IsPlayerOwner) {
				ClearWeaponInfo();
			}
		}
	}
	else {//есть первое оружие
		SetWeaponToSlot(0);
	}
}
void AChel::RefreshWidgetAmmoOwning(int32 NewLeftAmmo, int32 NewMaxAmmo, int32 NewCurIndex) {
	CurrentIndex = NewCurIndex;
	UserView->AmmoLabel->SetVisibility(ESlateVisibility::Visible);
	UserView->AmmoMax->SetVisibility(ESlateVisibility::Visible);
	UserView->WeaponName->SetVisibility(ESlateVisibility::Visible);
	UserView->AmmoSlash->SetVisibility(ESlateVisibility::Visible);
	UserView->AmmoLabel->SetText(FText::AsNumber(CurrentWeapons[CurrentIndex]->LeftAmmo));
	UserView->AmmoMax->SetText(FText::AsNumber(CurrentWeapons[CurrentIndex]->MaxAmmo));
	UserView->WeaponName->SetText(CurrentWeapons[CurrentIndex]->WeaponName);
}

void AChel::InvertMovement(float timeToOff)
{
	InverseCoeff = -1.f;
	AddChromaticInvet();
	AmountBottleEffects += 1;
	UserView->AddIconToPanel(6);

	FTimerHandle FuzeTimerHandle;
	World->GetTimerManager().SetTimer(FuzeTimerHandle, this, &AChel::RemoveInvertMovement, timeToOff, false);
}

void AChel::RemoveInvertMovement()
{
	AmountBottleEffects -= 1;
	if (InverseCoeff < 0 && AmountBottleEffects == 0) {
		InverseCoeff = 1.f;
		RemoveChromaticInvet();
		UserView->RemoveIconFromPanel(6);
	}
}

void AChel::RefreshWidgetAmmoOwningClient_Implementation(int32 NewLeftAmmo, int32 NewMaxAmmo, int32 NewCurIndex)
{
	RefreshWidgetAmmoOwning(NewLeftAmmo, NewMaxAmmo, NewCurIndex);
}

void AChel::SetWeaponToSlotMulticast_Implementation(int32 IndexWeapon)
{
	SetWeaponToSlot(IndexWeapon);
}
void AChel::ChangeAmmoClients_Implementation(int32 NewLeftAmmo, int32 indexWeapon)
{
	if(GetLocalRole() != ROLE_Authority && CurrentWeapons[indexWeapon])
		CurrentWeapons[indexWeapon]->LeftAmmo = NewLeftAmmo;
}

void AChel::ChangeAmmoMaxClients_Implementation(int32 NewMaxAmmmo, int32 indexWeapon)
{
	if (GetLocalRole() != ROLE_Authority && CurrentWeapons[indexWeapon])
		CurrentWeapons[indexWeapon]->MaxAmmo = NewMaxAmmmo;
}

void AChel::StartAnimInCurSlot_Implementation()
{
	if (IsPlayerOwner) {
		CanFireWeapon = false;
	}
	if (CurrentWeapons[CurrentIndex]) {
		CurrentWeapons[CurrentIndex]->AnimationThrow();
	}
}

void AChel::StartAnimInCurSlotReverse_Implementation(bool HaveAmmo)
{
	int32 idx = CurrentIndex; //на случай, еслы мы вызовем switchToFreeWeapon
	if (!HaveAmmo) {
		if (IsPlayerOwner) {
			CanFireWeapon = true;
		}
		if (CurrentWeapons[CurrentIndex]) {
			CurrentWeapons[CurrentIndex]->GunMesh->SetVisibility(false);
			SwitchToFreeWeapon();
		}
	}
	if(CurrentWeapons[idx])
		CurrentWeapons[idx]->AnimationThrowReverse();

}
void AChel::ClearWeaponInfo() {
	UserView->AmmoLabel->SetVisibility(ESlateVisibility::Hidden);
	UserView->AmmoMax->SetVisibility(ESlateVisibility::Hidden);
	UserView->WeaponName->SetVisibility(ESlateVisibility::Hidden);
	UserView->AmmoSlash->SetVisibility(ESlateVisibility::Hidden);
}

void AChel::ClearWeaponInfoClient_Implementation() {
	ClearWeaponInfo();
}

void AChel::GetAmmo_Server_Implementation() {
	GetAmmo_Multicast(CurrentWeapons[0]->LeftAmmo);
}

bool AChel::GetAmmo_Server_Validate() {
	return true;
}

void AChel::GetAmmo_Multicast_Implementation(int32 Ammmmmmo) {
	if (CurrentWeapons[0]) {
		CurrentWeapons[0]->LeftAmmo = Ammmmmmo;
		if (Ammmmmmo == 0) {
			CurrentWeapons[0]->GunMesh->SetVisibility(false);
		}
	}
}
void AChel::SwitchToFreeWeapon_Multicast_Implementation() {
	SwitchToFreeWeapon();
}

void AChel::HideCurrentWeapon_Implementation() {
	CurrentWeapons[CurrentIndex]->GunMesh->SetVisibility(false);
}

void AChel::SetWeaponToSlotServer_Implementation(int32 IndexWeapon) {
	SetWeaponToSlotMulticast(IndexWeapon);
}

bool AChel::SetWeaponToSlotServer_Validate(int32 IndexWeapon) {
	return true;
}

void AChel::CreateWeaponServer_Implementation(UClass* WeaponCreatedClass, int32 Amount, int32 IdexSlot) {
	CreateWeaponMulticast(WeaponCreatedClass, Amount, IdexSlot);
}

bool AChel::CreateWeaponServer_Validate(UClass* WeaponCreatedClass, int32 Amount, int32 IdexSlot) {
	return true;
}

void AChel::DropSpecialGun_Server_Implementation() {
	CurrentWeapons[1]->DropItem();
}

bool AChel::DropSpecialGun_Server_Validate() {
	return true;
}

void AChel::ChangeAmmoServer_Implementation(int32 NewLeftAmmmo, int32 indexWeapon) {
	CurrentWeapons[indexWeapon]->LeftAmmo = NewLeftAmmmo;
	ChangeAmmoClients(NewLeftAmmmo, indexWeapon);
}

bool AChel::ChangeAmmoServer_Validate(int32 NewLeftAmmmo, int32 indexWeapon) {
	return true;
}

void AChel::DeleteAllWeapons_Implementation() {
	for (int i = 0; i < CurrentWeapons.Num(); ++i) {
		if (CurrentWeapons[i])
			CurrentWeapons[i]->Destroy();
	}
}

void AChel::PickUpCoreItem_Implementation(int32 ItemType, const FText& ThrowNickName)
{
	UPlayerFindCoreItem* TmpWidget = Cast<UPlayerFindCoreItem>(CreateWidget(World, PlayerFindCoreItem_class));
	TmpWidget->NickName->SetText(ThrowNickName);
	switch (ItemType)
	{
	case 0:
	{
		TmpWidget->BoltorezImage->SetVisibility(ESlateVisibility::Visible);
		break;
	}
	case 1:
	{
		TmpWidget->KeyShelterImage->SetVisibility(ESlateVisibility::Visible);
		break;
	}
	case 2:
	{
		TmpWidget->OtvertkaImage->SetVisibility(ESlateVisibility::Visible);
		break;
	}
	}
	KillFeed->VB_KillFeed->AddChild(TmpWidget);
}