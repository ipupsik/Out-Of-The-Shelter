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
#include "Cache_Key.h"
#include "CanalizationDamageCollision.h"
#include "Code_Note.h"
#include "BP_VentilaciaRubilnick.h"
#include "CoreItem.h"
#include "Weapon_Character.h"
#include "ConsumableAbility.h"

enum AreaType
{
	Canalizacia,
	Shelter,
	Ventilacia,
	ShelterOpener
};

enum PickUpType {
	Boltorez,
	KeyShelter,
	Otvertka,
	OpenArea,
	Cache,
	CacheKey,
	GeneratorArea,
	CanalizationButton,
	WebCamLocker,
	InvisiblePotion,
	CodeNote,
	ClickButton,
	AmmoBackPack,
	RentgenGlasses,
	ChelsDetector,
	HealthPacket,
	DoubleArmAbility,
	Shields,
	StoneDamageBuff,
	RadiationAntidot,
	SpeedBust,
	VentilaciaRubilnick,
	StoneDamageBuffTemp,
	ImmortalPotion,
	NasosZatichka,
};

enum CacheType {
	KeyBronze,
	KeySilver,
	KeyGold
};

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

	StoneRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StoneRight"));
	StoneRight->SetupAttachment(WeaponPosition);

	StoneLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StoneLeft"));
	StoneLeft->SetupAttachment(WeaponPosition);

	TimeLine_Stone_First = CreateDefaultSubobject<UTimelineComponent>(TEXT("ThrowStoneFirst"));
	TimeLine_Stone_Second = CreateDefaultSubobject<UTimelineComponent>(TEXT("ThrowStoneSecond"));
	TimeLine_Stone_First_Left = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimeLine_Stone_First_Left"));
	TimeLine_Stone_Second_Left = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimeLine_Stone_Second_Left"));
	TimeLine_FOV_WebCam = CreateDefaultSubobject<UTimelineComponent>(TEXT("FOV_WebCam"));

	//Говорим делегатам, какую функцию подцепить для Update и для OnFinished
	InterpFunction_Stone.BindUFunction(this, FName("TimelineVectorReturn_Stone"));
	InterpFunction_Stone_Left.BindUFunction(this, FName("TimelineVectorReturn_Stone_Left"));

	InterpFunction_FOV_WebCam.BindUFunction(this, FName("TimelineFloatReturn_FOV_WebCam"));

	TimelineFinished_Stone_First.BindUFunction(this, FName("OnTimelineFinished_Stone_First"));
	TimelineFinished_Stone_Second.BindUFunction(this, FName("OnTimelineFinished_Stone_Second"));

	TimelineFinished_Stone_First_Left.BindUFunction(this, FName("OnTimelineFinished_Stone_First_Left"));
	TimelineFinished_Stone_Second_Left.BindUFunction(this, FName("OnTimelineFinished_Stone_Second_Left"));

	DamageCollision->OnComponentBeginOverlap.AddDynamic(this, &AChel::OnOverlapBegin);

	IsAlreadyCreated = false;
	LastRAbilityIndex = -1;
	DoesNotImmortal = 1;
	CurrentStoneDamageBuffTempCount = 0;
	StoneDamageBuffTempValue = 1.0f;
	SpeedBustValue = 0;
	DoesRadiationAntidot = 1;
	StoneDamageBuffCount = 0;
	ShieldsCount = 0;
	Health = 0;
	bIsAlreadyThrowing = false;
	IsInGame = false;
	Ammo = MaxAmmoCount;
	bLineTrace_is_need_refresh = false;
	DoesHave_Owner = false;
	ItemCodePickUp = -1;
	IsNotInWebCam = true;
	CanThrowStone = true;
	CanFireWeapon = true;
	WebCamIterator = -1;
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
	bInEscMenu = false;
//	OpenAreaObj = nullptr;
	TickEnableGeneratorWidget = false;
	KeysCount.Init(0, 3);
	TargetItemsStatic.Init(nullptr, 0);
	TargetArrowsStatic.Init(nullptr, 0);
	TargetArrowsDynamic.Init(nullptr, 0);
	TargetItemsDynamic.Init(nullptr, 0);
	MyKDA_Stat.Init(nullptr, 4);
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
			UE_LOG(LogTemp, Warning, TEXT("lla"))
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

void AChel::EnableRentgen()
{
	IsRentgenRender = true;
	SenseCollision->SetRenderCustomDepth(true);
	SenseCollision->MarkRenderStateDirty();

	TArray<AActor*>RentgenItems1;
	SenseCollision->GetOverlappingActors(RentgenItems1, GS->Boltorez);
	for (auto& it : RentgenItems1)
	{
		APickableItem* RentgenOverlappItem = Cast<APickableItem>(it);
		RentgenOverlappItem->Item->SetRenderCustomDepth(true);
		RentgenOverlappItem->Item->MarkRenderStateDirty();
		UE_LOG(LogTemp, Warning, TEXT("Find Boltorez"));
	}
	TArray<AActor*>RentgenItems2;
	SenseCollision->GetOverlappingActors(RentgenItems2, GS->KeyShelter);
	for (auto& it : RentgenItems2)
	{
		APickableItem* RentgenOverlappItem = Cast<APickableItem>(it);
		RentgenOverlappItem->Item->SetRenderCustomDepth(true);
		RentgenOverlappItem->Item->MarkRenderStateDirty();
		UE_LOG(LogTemp, Warning, TEXT("Find KeyShelter"));
	}
	TArray<AActor*>RentgenItems3;
	SenseCollision->GetOverlappingActors(RentgenItems3, GS->Otvertka);
	for (auto& it : RentgenItems3)
	{
		APickableItem* RentgenOverlappItem = Cast<APickableItem>(it);
		RentgenOverlappItem->Item->SetRenderCustomDepth(true);
		RentgenOverlappItem->Item->MarkRenderStateDirty();
		UE_LOG(LogTemp, Warning, TEXT("Find Otvertka"));
	}
}

void AChel::DisableRentgen()
{
	IsRentgenRender = false;
	SenseCollision->SetRenderCustomDepth(false);
	SenseCollision->MarkRenderStateDirty();

	TArray<AActor*>RentgenItems1;
	SenseCollision->GetOverlappingActors(RentgenItems1, GS->Boltorez);
	for (auto& it : RentgenItems1)
	{
		APickableItem* RentgenOverlappItem = Cast<APickableItem>(it);
		RentgenOverlappItem->Item->SetRenderCustomDepth(false);
		RentgenOverlappItem->Item->MarkRenderStateDirty();
	}
	TArray<AActor*>RentgenItems2;
	SenseCollision->GetOverlappingActors(RentgenItems2, GS->KeyShelter);
	for (auto& it : RentgenItems2)
	{
		APickableItem* RentgenOverlappItem = Cast<APickableItem>(it);
		RentgenOverlappItem->Item->SetRenderCustomDepth(false);
		RentgenOverlappItem->Item->MarkRenderStateDirty();
	}
	TArray<AActor*>RentgenItems3;
	SenseCollision->GetOverlappingActors(RentgenItems3, GS->Otvertka);
	for (auto& it : RentgenItems3)
	{
		APickableItem* RentgenOverlappItem = Cast<APickableItem>(it);
		RentgenOverlappItem->Item->SetRenderCustomDepth(false);
		RentgenOverlappItem->Item->MarkRenderStateDirty();
	}
}

void AChel::QAbilityEnable()
{
	if (QAbilityType != -1)
	{
		switch (QAbilityType)
		{
		case RentgenGlasses:
		{
			EnableRentgen();
			break;
		}
		case ChelsDetector:
		{
			EnableChelDetector();
			break;
		}
		}
	}
}

void AChel::QAbilityDisable()
{
	if (QAbilityType != -1)
	{
		switch (QAbilityType)
		{
		case RentgenGlasses:
		{
			DisableRentgen();
			break;
		}
		case ChelsDetector:
		{
			DisableChelDetector();
			break;
		}
		}
	}
}

void AChel::RAbilityEnable()
{
	if (RAbilityTypeIndex != -1)
	{
		switch (RAbilityPanel[RAbilityTypeIndex]->AbilityType)
		{
		case HealthPacket:
		{
			UseRAbility();
			RAbility_HealPacket();
			break;
		}
		case SpeedBust:
		{
			UseRAbility();
			UseSpeedBust_Server();
			SpeedBustValue = 300;
			GetCharacterMovement()->MaxWalkSpeed = 800.f + SpeedBustValue;
			CurrentSpeedBustCount++;
			FTimerHandle FuzeTimerHandle;
			GetWorld()->GetTimerManager().SetTimer(FuzeTimerHandle, this, &AChel::StopUseSpeedBust, 20, false);
			break;
		}
		case StoneDamageBuffTemp:
		{
			UseRAbility();
			AddStoneDamageBuffTemp();
			break;
		}
		case ImmortalPotion:
		{
			UseRAbility();
			AddImmortalServer();
			break;
		}
		}

	}
}

/*void AChel::RAbilityDisable()
{
	if (RAbilityType != -1)
	{
		switch (RAbilityType)
		{

		}
	}
}*/

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
	StonePositionRight = StoneRight->GetRelativeLocation();
	StonePositionLeft = StoneLeft->GetRelativeLocation();
	World = GetWorld();
	GI = World->GetGameInstance<UGI>();

	Cast<AChel>(UGameplayStatics::GetPlayerCharacter(World, 0))->PlayersArray.Add(this);

	if (vCurveStone) {
		//Подцепляем эти функции для TimeLine
		TimeLine_Stone_First->AddInterpVector(vCurveStone, InterpFunction_Stone);
		TimeLine_Stone_First->SetTimelineFinishedFunc(TimelineFinished_Stone_First);

		TimeLine_Stone_First->SetLooping(false);
		TimeLine_Stone_First->SetIgnoreTimeDilation(true);

		TimeLine_Stone_Second->AddInterpVector(vCurveStone, InterpFunction_Stone);
		TimeLine_Stone_Second->SetTimelineFinishedFunc(TimelineFinished_Stone_Second);

		TimeLine_Stone_Second->SetLooping(false);
		TimeLine_Stone_Second->SetIgnoreTimeDilation(true);
		//-----------------------------------------------
		TimeLine_Stone_First_Left->AddInterpVector(vCurveStone, InterpFunction_Stone_Left);
		TimeLine_Stone_First_Left->SetTimelineFinishedFunc(TimelineFinished_Stone_First_Left);

		TimeLine_Stone_First_Left->SetLooping(false);
		TimeLine_Stone_First_Left->SetIgnoreTimeDilation(true);

		TimeLine_Stone_Second_Left->AddInterpVector(vCurveStone, InterpFunction_Stone_Left);
		TimeLine_Stone_Second_Left->SetTimelineFinishedFunc(TimelineFinished_Stone_Second_Left);

		TimeLine_Stone_Second_Left->SetLooping(false);
		TimeLine_Stone_Second_Left->SetIgnoreTimeDilation(true);
	}

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
		KillFeed->AddToViewport();

		UserView->Player = this;
		UserView->AmmoLabel->SetText(FText::AsNumber((int32)Ammo));

		TArray<UWidget*>InventoryRArray = MyInventory->RAbilityPanel->GetAllChildren();;
		for (auto& it : InventoryRArray)
		{
			RAbilityPanel.Add(Cast<URAbilitySlot>(it));
		}

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
}

void AChel::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	MyBeginPlay();
}

void AChel::ChangeCorretcaPosition(int32 TypeChange) {
	GeneratorView->Corretca->SetValue(GeneratorView->PositionX[TypeChange]);
	GeneratorView->PB_Repair->SetPercent(0.0f);
	bToRight = true;
	GeneratorView->curSpeed = GeneratorView->Speed[TypeChange];
}

// Called every frame
void AChel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (IsInGame == true) {
		if (IsServerAuth) {
			Health += DeltaTime * 2 * 0.01f * RadCoeff * CanalizationDamage / 1.5f * DoesRadiationAntidot * DoesNotImmortal;
			if (Health > 1.0f) {
				if (DoesHave[Boltorez])
					GS->CurrentBoltorez--;
				if (DoesHave[KeyShelter])
					GS->CurrentKeyShelter--;
				if (DoesHave[Otvertka])
					GS->CurrentOtvertka--;

				TArray<AActor*>Players;
				UGameplayStatics::GetAllActorsOfClass(World, StaticClass(), Players);
				for (auto& Player : Players) {
					Cast<AChel>(Player)->RefreshWidgets(DoesHave, KillerIndex, Index);
				}
				DoesHave.Init(false, 3);
				bCanWalkingAndWatching = true;
				KillPlayer();
				return;
			}
		}

		if (IsPlayerOwner) {
			if (TickEnableGeneratorWidget) {
				if (bToRight) {
					GeneratorView->PB_Repair->SetPercent(GeneratorView->PB_Repair->Percent + (GeneratorView->curSpeed) * DeltaTime);
					if (GeneratorView->PB_Repair->Percent >= 1.0f) {
						bToRight = false;
					}
				}
				else {
					GeneratorView->PB_Repair->SetPercent(GeneratorView->PB_Repair->Percent - (GeneratorView->curSpeed) * DeltaTime);
					if (GeneratorView->PB_Repair->Percent <= 0.0f) {
						bToRight = true;
					}
				}
			}

			UserView->RadiationPoints->SetPercent(Health);
			UserView->DarkScreen->SetRenderOpacity(Health);

			FHitResult OutHit;

			FVector StartLocation = CameraComp->GetComponentLocation();
			FVector EndLocation = StartLocation + CameraComp->GetForwardVector() * 300;

			FCollisionQueryParams CollisionParams;

			//DrawDebugLine(World, StartLocation, EndLocation, FColor::Red, false, 1, 0, 1);

			isTracedBad = false; //Предположим, что мы нашли лайн трейсом нужные нам предметы
			if (World->LineTraceSingleByChannel(OutHit, StartLocation, EndLocation, ECC_Visibility, CollisionParams))
			{
				if (OutHit.bBlockingHit)
				{
					AActor* HittableActor = OutHit.GetActor();
					if (HittableActor) { //Если мы стукнулись в какой-то актор, а не в пустоту
						APickableItem* TracedItem = Cast<APickableItem>(HittableActor);
						if (TracedItem) { //Если мы стукнулись в нужный нам предмет
							ItemCodePickUp = TracedItem->Type;
							if (TracedItem->Type != ClickButton && TracedItem->Type != VentilaciaRubilnick)
								UserView->E_Mark->SetVisibility(ESlateVisibility::Visible);
							if (LastItem && LastItem != TracedItem) {
								LastItem->Item->SetRenderCustomDepth(false);
								LastItem->Item->MarkRenderStateDirty();
							}
							if (LastItem != TracedItem) {
								LastItem = TracedItem;
								bLineTrace_is_need_refresh = true;
								if (TracedItem->Type == OpenArea) {
									AOpenArea* MyOpenArea = Cast<AOpenArea>(TracedItem);
									if (!MyOpenArea->bIsAvaliable) {
										UserView->E_Mark->SetVisibility(ESlateVisibility::Hidden);
									}
									else {
										LastItem->Item->SetRenderCustomDepth(true);
										LastItem->Item->MarkRenderStateDirty();
									}
								}
								else if (TracedItem->Type == VentilaciaRubilnick) {
									ABP_VentilaciaRubilnick* MyVentilaciaRubilnick = Cast<ABP_VentilaciaRubilnick>(TracedItem);
									UE_LOG(LogTemp, Warning, TEXT("Enable - %d"), (int)MyVentilaciaRubilnick->is_Avaliable);
									if (MyVentilaciaRubilnick->is_Avaliable) {
										UserView->E_Mark->SetVisibility(ESlateVisibility::Visible);
										LastItem->Item->SetRenderCustomDepth(true);
										LastItem->Item->MarkRenderStateDirty();
									}
								}
								else if (TracedItem->Type >= 0 && TracedItem->Type <= 2)
								{
									if (DoesHave[LastItem->Type]) {
										LastItem->Item->SetRenderCustomDepth(true);
										LastItem->Item->SetCustomDepthStencilValue(1);
										LastItem->Item->MarkRenderStateDirty();
									}
									else
									{
										LastItem->Item->SetRenderCustomDepth(true);
										LastItem->Item->SetCustomDepthStencilValue(2);
										LastItem->Item->MarkRenderStateDirty();
									}
								}
								else if (TracedItem->Type == ClickButton)
								{
									if (GS->IsShelterAvaliable) {
										UserView->E_Mark->SetVisibility(ESlateVisibility::Visible);
										LastItem->Item->SetRenderCustomDepth(true);
										LastItem->Item->MarkRenderStateDirty();
									}
								}
								else
								{
									LastItem->Item->SetRenderCustomDepth(true);
									LastItem->Item->MarkRenderStateDirty();
								}
							}
						}
						else
						{
							ACache* TracedCache = Cast<ACache>(HittableActor);
							if (TracedCache) {
								if (LastItem) {
									LastItem->Item->SetRenderCustomDepth(false);
									LastItem->Item->MarkRenderStateDirty();
								}
								if (TracedCache->IsEnabled && KeysCount[TracedCache->CacheType] > 0) {
									bLineTrace_is_need_refresh = true;
									ItemCodePickUp = Cache;
									UserView->E_Mark->SetVisibility(ESlateVisibility::Visible);

									LastCache = TracedCache;
								}
								else
								{
									UserView->E_Mark->SetVisibility(ESlateVisibility::Hidden);
								}
							}
							else
							{
								AButtonCanalization* TracedButton = Cast<AButtonCanalization>(HittableActor);
								if (TracedButton) {
									bLineTrace_is_need_refresh = true;
									ItemCodePickUp = CanalizationButton;
									UserView->E_Mark->SetVisibility(ESlateVisibility::Visible);

									LastButton = TracedButton;
								}
								else
								{
									AWebCamLocker* TracedWebCamLocker = Cast<AWebCamLocker>(HittableActor);
									if (TracedWebCamLocker)
									{
										bLineTrace_is_need_refresh = true;
										ItemCodePickUp = WebCamLocker;
										UserView->E_Mark->SetVisibility(ESlateVisibility::Visible);
										TracedWebCamLocker->Mesh->SetRenderCustomDepth(true);
										TracedWebCamLocker->Mesh->SetCustomDepthStencilValue(2);
										TracedWebCamLocker->Mesh->MarkRenderStateDirty();
										LastWebCamLocker = TracedWebCamLocker;
									}
									else
									{
										ADezinfectorNasosZatichka* TracedNasosZatichka = Cast<ADezinfectorNasosZatichka>(HittableActor);
										if (TracedNasosZatichka)
										{
											bLineTrace_is_need_refresh = true;
											ItemCodePickUp = NasosZatichka;
											UserView->E_Mark->SetVisibility(ESlateVisibility::Visible);
											LastZatichka = TracedNasosZatichka;
										}
										else
											isTracedBad = true; //Мы не попали в нужный нам предмет
									}
								}
							}
						}
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
				UE_LOG(LogTemp, Warning, TEXT("Widget Update"));
				ItemCodePickUp = -1;
				if (LastItem)
				{
					if (LastItem->Type <= 2 && !IsRentgenRender) {
						LastItem->Item->SetRenderCustomDepth(false);
						LastItem->Item->MarkRenderStateDirty();
					}
					else if (LastItem->Type > 2)
					{
						LastItem->Item->SetRenderCustomDepth(false);
						LastItem->Item->MarkRenderStateDirty();
					}
				}

				if (LastWebCamLocker)
				{
					LastWebCamLocker->Mesh->SetRenderCustomDepth(false);
					LastWebCamLocker->Mesh->MarkRenderStateDirty();
				}

				if (LastItem && Cast<AOpenArea>(LastItem))
				{
					PickUp_Released();
				}
				UserView->StopAllAnimations();
				UserView->E_Mark->SetVisibility(ESlateVisibility::Hidden);
				LastItem = nullptr;
				LastWebCamLocker = nullptr;
			}
		}
	}

	if (IsPlayerOwner) {
		for (int i = 0; i < TargetArrowsStatic.Num(); ++i)
		{
			UpdateTargetArrowPosition(TargetItemsStatic[i], TargetArrowsStatic[i]);
		}
		//UE_LOG(LogTemp, Warning, TEXT("TargetItemsDynamic.Num - %d"), TargetItemsDynamic.Num());
		//UE_LOG(LogTemp, Warning, TEXT("TargetArrowsDynamic.Num - %d"), TargetArrowsDynamic.Num());
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
	PlayerInputComponent->BindAction("ThrowStoneRight", IE_Pressed, this, &AChel::ThrowStoneRight);
	PlayerInputComponent->BindAction("ThrowStoneLeft", IE_Pressed, this, &AChel::ThrowStoneLeft);
	PlayerInputComponent->BindAction("PickUp", IE_Pressed, this, &AChel::PickUp);
	PlayerInputComponent->BindAction("PickUp", IE_Released, this, &AChel::PickUp_Released);
	PlayerInputComponent->BindAction("Opening", IE_Pressed, this, &AChel::OpenAreaPressed);
	PlayerInputComponent->BindAction("Opening", IE_Released, this, &AChel::OpenAreaReleased);
	PlayerInputComponent->BindAction("UpdateSpectating_Left", IE_Released, this, &AChel::UpdateSpectating_Left);
	PlayerInputComponent->BindAction("UpdateSpectating_Right", IE_Released, this, &AChel::UpdateSpectating_Right);
	PlayerInputComponent->BindAction("QAbility", IE_Pressed, this, &AChel::QAbilityEnable);
	PlayerInputComponent->BindAction("QAbility", IE_Released, this, &AChel::QAbilityDisable);
	PlayerInputComponent->BindAction("RAbility", IE_Pressed, this, &AChel::RAbilityEnable);
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

void AChel::OpenAreaPressed() 
{
	if (!bInEscMenu && bCanWalkingAndWatching) {
		if (AreaCode != -1)
		{
			IsSuccessOpening = true;
			if (AreaCode <= 2 && AreaCode >= 0) {
				if (!GS->AreaAvaliables[AreaCode] && DoesHave[AreaCode]) {
					UserView->PB_Opening->SetVisibility(ESlateVisibility::Visible);
					UserView->TimeLeft->SetVisibility(ESlateVisibility::Visible);
				}
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
				if (DoesHave[AreaCode] && !GS->AreaAvaliables[AreaCode])
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
			case GeneratorArea:
			{
				if (GenAreaObj) {
					if (GenAreaObj->IsAvalible) {
						if (GeneratorView->IsVisible()) {
							if (GeneratorView->Corretca->Value <= GeneratorView->PB_Repair->Percent) {
								ChangeGeneratorStas();
							}
							else {
								ChangeCorretcaPosition(GenAreaObj->Stadiya);
								OutlineBad_Server();//Здесь могла быть ваша логика с обводкой конкретного челика для всех остальных, но уже 12 часов ночи, сори, бб
							}
						}
						else {
							UserView->HoldText->SetVisibility(ESlateVisibility::Hidden);
							ChangeCorretcaPosition(GenAreaObj->Stadiya);
							TickEnableGeneratorWidget = true;
							GeneratorView->SetVisibility(ESlateVisibility::Visible);
						}
					}
				}
				break;
			}
			case ShelterOpener:
			{
				if (GS->AreaAvaliables[1]) {
					PlayerEscape(1);
					UserView->RemoveFromParent();
				}
			}
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

void AChel::AddChromaticAbberationClient_Implementation()
{
	AddChromaticAbberation();
}

//TimelineAnimation
void AChel::OnTimelineFinished_Stone_First() {
	TimeLine_Stone_Second->ReverseFromEnd();
	if (IsPlayerOwner)
	{
		PlayStoneThrowSound();
	}

	StoneCountUpdate(Ammo);

	FTransform trans;
	trans.SetLocation(FVector(GetActorLocation().X, GetActorLocation().Y, StoneRight->GetComponentLocation().Z));
	trans.SetRotation(FQuat(StoneRight->GetComponentRotation()));

	AStone* NewStone = World->SpawnActorDeferred<AStone>(StoneClass, trans, this, this, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	NewStone->Index = Index;
	NewStone->StoneDamage = (STONE_DAMAGE + 0.02 * StoneDamageBuffCount) * StoneDamageBuffTempValue;
	UGameplayStatics::FinishSpawningActor(NewStone, trans);
	if (Ammo == 0) {
		HideStoneMulticast();
	}
}

void AChel::OnTimelineFinished_Stone_First_Left()
{
	TimeLine_Stone_Second_Left->ReverseFromEnd();
	if (IsPlayerOwner)
	{
		PlayStoneThrowSound();
	}

	StoneCountUpdate(Ammo);

	FTransform trans;
	trans.SetLocation(FVector(GetActorLocation().X, GetActorLocation().Y, StoneLeft->GetComponentLocation().Z));
	trans.SetRotation(FQuat(StoneLeft->GetComponentRotation()));

	AStone* NewStone = World->SpawnActorDeferred<AStone>(StoneClass, trans, this, this, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	NewStone->Index = Index;
	NewStone->StoneDamage = (STONE_DAMAGE + 0.02 * StoneDamageBuffCount) * StoneDamageBuffTempValue;
	UGameplayStatics::FinishSpawningActor(NewStone, trans);
	if (Ammo == 0) {
		HideStoneMulticast();
	}
}

void AChel::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AStone* OverStone = Cast<AStone>(OtherActor);
	if (IsServerAuth) {
		if (OverStone) {
			if (OverStone->Index != Index)
			{
				StoneAttack(OverStone->Index, OverStone->StoneDamage);
				TArray<AActor*>Players;
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), AChel::StaticClass(), Players);
				for (int i = 0; i < Players.Num(); i++) {
					AChel* Chel = Cast<AChel>(Players[i]);
					if (Chel->Index == OverStone->Index)
					{
						Chel->AddHitMarker();
						break;
					}
				}
				PlayStoneHit();
				OverStone->Destroy();
			}
		}
	}
	else
	{
		if (OverStone->Index != Index)
		{
			OverStone->Destroy();
		}
	}
}

void AChel::StoneCountUpdate_Implementation(int32 Count)
{
	if (IsPlayerOwner)
		UserView->AmmoLabel->SetText(FText::AsNumber(Count));
}

void AChel::TimelineVectorReturn_Stone(FVector value) {
	StoneRight->SetRelativeLocation(StonePositionRight + value);
}

void AChel::TimelineVectorReturn_Stone_Left(FVector value) {
	StoneLeft->SetRelativeLocation(StonePositionLeft + value);
}

void AChel::TimelineFloatReturn_FOV_WebCam(float value)
{
	CameraComp->SetFieldOfView(value);
}

void AChel::OnTimelineFinished_Stone_Second() {
	bIsAlreadyThrowing = false;
}

void AChel::OnTimelineFinished_Stone_Second_Left() {
	bIsAlreadyThrowingLeft = false;
}
//-----------------------------

//AttackInput------------------
void AChel::ThrowStoneRight() {
	if (DoubleArmThrowing) {
		if (Ammo > 0 && IsNotInWebCam && bCanWalkingAndWatching && !bInEscMenu && CanThrowStone) {
			if (!bIsAlreadyThrowing) {
				bIsAlreadyThrowing = true;
				TimeLine_Stone_First->PlayFromStart();
				ThrowStoneServer(true);
			}
		}
	}
}

void AChel::ThrowStoneLeft() {
	if (!DoubleArmThrowing) {
		if (Ammo > 0 && IsNotInWebCam && bCanWalkingAndWatching && !bInEscMenu && CanThrowStone) {
			if (!bIsAlreadyThrowing) {
				bIsAlreadyThrowing = true;
				TimeLine_Stone_First->PlayFromStart();
				ThrowStoneServer(true);
			}
		}
	}
	else
	{
		if (Ammo > 0 && IsNotInWebCam && bCanWalkingAndWatching && !bInEscMenu && CanThrowStone) {
			if (!bIsAlreadyThrowingLeft) {
				bIsAlreadyThrowingLeft = true;
				TimeLine_Stone_First_Left->PlayFromStart();
				ThrowStoneServer(false);
			}
		}
	}
}

void AChel::ThrowStoneMulticast_Implementation(bool Type)
{
	if (!IsPlayerOwner)
	{
		if (Type) {
			TimeLine_Stone_First->PlayFromStart();
		}
		else
		{
			TimeLine_Stone_First_Left->PlayFromStart();
		}
	}
}

void AChel::ThrowStoneServer_Implementation(bool Type)
{
	--Ammo;
	ThrowStoneMulticast(Type);
	TArray<AActor*> OverlappngActors;
	GetOverlappingActors(OverlappngActors, AAmmoPoint::StaticClass());
	for (auto& it : OverlappngActors) {
		AAmmoPoint* AmPt = Cast<AAmmoPoint>(it);
		if (AmPt) {
			UE_LOG(LogTemp, Warning, TEXT("UpdatingAmmo-Server"));
			AmPt->AmmoUpdate();
			break;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Complete Throwing stone - server"));
}

bool AChel::ThrowStoneServer_Validate(bool Type)
{
	return true;
}

void AChel::HideStoneMulticast_Implementation() {
	StoneRight->SetHiddenInGame(true);
	if (DoubleArmThrowing)
		StoneLeft->SetHiddenInGame(true);
}

void AChel::ShowStoneMulticast_Implementation() {
	StoneRight->SetHiddenInGame(false);
	if (DoubleArmThrowing)
		StoneLeft->SetHiddenInGame(false);
}
//----------------------------

//KeyBoardInput----------------
void AChel::GoForward(float input) {
	if (bCanWalkingAndWatching && !bInEscMenu) {
		if (input != 0.0f && IsNotInWebCam && CanThrowStone) {
			AddMovementInput(GetActorForwardVector(), input * MoveCoeff);
		}
	}
}

void AChel::GoRight(float input) {
	if (bCanWalkingAndWatching && !bInEscMenu) {
		if (input != 0.0f && IsNotInWebCam && CanThrowStone) {
			AddMovementInput(GetActorRightVector(), input * MoveCoeff);
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
	if (bCanWalkingAndWatching && !bInEscMenu) {
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
	if (bCanWalkingAndWatching && !bInEscMenu) {
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
	if (bCanWalkingAndWatching) {
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
	SpawnDeadSound();
	UserView->PlayAnimation(UserView->Shading);
	FTimerHandle FuzeTimerHandle;
	World->GetTimerManager().SetTimer(FuzeTimerHandle, this, &AChel::SleepAnimation_End, 2.0f, false);
}

void AChel::SleepAnimation_End()
{
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
	StoneCountUpdate(MaxAmmoCount);

	WebCamUI->SetVisibility(ESlateVisibility::Hidden);

	UserView->SetVisibility(ESlateVisibility::Visible);
	SpawnWakeUpSound();
	UserView->PlayAnimation(UserView->Shading, 0, 1, EUMGSequencePlayMode::Type::Reverse);
}

//-----------------------------
void AChel::PickUp() {
	if (!bInEscMenu) {
		if (IsNotInWebCam) {
			if (ItemCodePickUp != -1) {
				UE_LOG(LogTemp, Warning, TEXT("ItemCode - %d"), ItemCodePickUp);
				IsSuccessOpening = true;
				switch (ItemCodePickUp) {
				case Boltorez:
				{
					if (!DoesHave[Boltorez]) {
						UserView->WS_Boltorez->SetActiveWidgetIndex(1);
						DoesHave_Owner = true;
						LastItem->Item->SetRenderCustomDepth(false);
						LastItem->Item->MarkRenderStateDirty();
						LastItem = nullptr;
						NewHaveItemServer(Boltorez);
						MainExis_Canalizacia->Mesh->SetRenderCustomDepth(true);
						MainExis_Canalizacia->Mesh->MarkRenderStateDirty();
						PickUpSound();
					}
					break;
				}
				case KeyShelter:
				{
					if (!DoesHave[KeyShelter]) {
						UserView->WS_KeyShelter->SetActiveWidgetIndex(1);
						DoesHave_Owner = true;
						LastItem->Item->SetRenderCustomDepth(false);
						LastItem->Item->MarkRenderStateDirty();
						LastItem = nullptr;
						NewHaveItemServer(KeyShelter);
						MainExis_Shelter->Mesh->SetRenderCustomDepth(true);
						MainExis_Shelter->Mesh->MarkRenderStateDirty();
						PickUpSound();
					}
					break;
				}
				case Otvertka:
				{
					if (!DoesHave[Otvertka]) {
						UserView->WS_Otvertka->SetActiveWidgetIndex(1);
						DoesHave_Owner = true;
						LastItem->Item->SetRenderCustomDepth(false);
						LastItem->Item->MarkRenderStateDirty();
						LastItem = nullptr;
						NewHaveItemServer(Otvertka);
						MainExis_Ventilacia->Mesh->SetRenderCustomDepth(true);
						MainExis_Ventilacia->Mesh->MarkRenderStateDirty();
						PickUpSound();
					}
					break;
				}
				case CacheKey:
				{
					int KeyType = Cast<ACache_Key>(LastItem)->KeyType;
					switch (KeyType)
					{
					case KeyBronze:
					{
						UserView->KeyLeft_Bronze->SetText(FText::AsNumber(KeysCount[KeyBronze] + 1));
						break;
					}
					case KeySilver:
					{
						UserView->KeyLeft_Silver->SetText(FText::AsNumber(KeysCount[KeySilver] + 1));
						break;
					}
					case KeyGold:
					{
						UserView->KeyLeft_Gold->SetText(FText::AsNumber(KeysCount[KeyGold] + 1));
						break;
					}
					}
					KeysCount[KeyType]++;
					DoesHave_Owner = true;
					LastItem->Item->SetRenderCustomDepth(false);
					LastItem->Item->MarkRenderStateDirty();
					LastItem = nullptr;
					NewHaveItemServer(ItemCodePickUp);
					PickUpSound();
					break;
				}
				case Cache:
				{
					if (LastCache != nullptr) {
						if (KeysCount[LastCache->CacheType] > 0 && LastCache->IsEnabled)
						{
							if (!IsServerAuth)
								LastCache->IsEnabled = false;
							switch (LastCache->CacheType)
							{
							case KeyBronze:
							{
								UserView->KeyLeft_Bronze->SetText(FText::AsNumber(KeysCount[KeyBronze] - 1));
								break;
							}
							case KeySilver:
							{
								UserView->KeyLeft_Silver->SetText(FText::AsNumber(KeysCount[KeySilver] - 1));
								break;
							}
							case KeyGold:
							{
								UserView->KeyLeft_Gold->SetText(FText::AsNumber(KeysCount[KeyGold] - 1));
								break;
							}
							}
							KeysCount[LastCache->CacheType]--;
							UserView->E_Mark->SetVisibility(ESlateVisibility::Hidden);
							ChangeIsAvaliableCache();
						}
					}
					else
					{
						UE_LOG(LogTemp, Warning, TEXT("LastCache is nullptr"))
					}
					break;

				}
				case CanalizationButton:
				{
					UserView->E_Mark->SetVisibility(ESlateVisibility::Hidden);
					ChangeButtonCount_Server();
					break;
				}
				case WebCamLocker:
				{
					LockWebCam_Server();
					break;
				}
				case InvisiblePotion:
				{
					AddInvisibleServer();
					LastItem = nullptr;
					break;
				}
				case CodeNote:
				{
					if (Widget_Note->IsVisible())
					{
						Widget_Note->SetVisibility(ESlateVisibility::Hidden);
						PickUpSound();
						bCanWalkingAndWatching = true;
					}
					else
					{
						Widget_Note->ChangeText(GS->CodeGenerator);
						Widget_Note->SetVisibility(ESlateVisibility::Visible);
						PickUpSound();
						bCanWalkingAndWatching = false;
					}
					break;
				}
				case ClickButton:
				{
					AClickButton* CurButton = Cast<AClickButton>(LastItem);
					if (GS->IsShelterAvaliable && !GS->ButtonPlayAnim && CurButton)
					{
						if (CurButton->ButtonType <= 9) {
							if (GS->NumbersOnPanel.Num() <= 4) {
								AddNumToTerminalServer(CurButton->ButtonType);
								ButtonPressAnimationServer();
							}
						}
						else {
							if (CurButton->ButtonType == 10) {
								if (GS->NumbersOnPanel.Num() > 0) {
									DeleteLAstNumServer();
									ButtonPressAnimationServer();
								}
							}
							else
							{
								CheckCodeServer();
								ButtonPressAnimationServer();
							}
						}
					}
					break;
				}
				case OpenArea:
				{
					AOpenArea* CurOpArea = Cast<AOpenArea>(LastItem);
					if (!CurOpArea->bIsUsed)
					{
						if (CurOpArea != nullptr && CurOpArea->bIsAvaliable) {
							UserView->PB_Opening->SetVisibility(ESlateVisibility::Visible);
							UserView->TimeLeft->SetVisibility(ESlateVisibility::Visible);
						}
						UserView->PlayAnimation(UserView->OpenAreaAnim, CurOpArea->CurTimeVentil);
						GoToServerOpenArea(true);
						break;
					}
				}
				case AmmoBackPack:
				{
					UserView->AmmoMax->SetText(FText::AsNumber(MaxAmmoCount + 5));
					if (!IsServerAuth)
						MaxAmmoCount += 5;
					NewHaveItemServer(ItemCodePickUp);
					break;
				}
				case RentgenGlasses:
				{
					if (QAbilityType != -1)
						QAbilityDisable();
					NewHaveItemServer(RentgenGlasses, QAbilityType);
					QAbilityType = RentgenGlasses;
					break;
				}
				case ChelsDetector:
				{
					if (QAbilityType != -1)
						QAbilityDisable();
					NewHaveItemServer(ChelsDetector, QAbilityType);
					QAbilityType = ChelsDetector;
					break;
				}
				case HealthPacket:
				{
					if (LastRAbilityIndex < 2)
					{
						NewRAbility(HealthPacket);
						NewHaveItemServer(HealthPacket);
					}
					break;
				}
				case DoubleArmAbility:
				{
					if (!DoubleArmThrowing) {
						StoneLeft->SetHiddenInGame(false);
						DoubleArmThrowing = true;
						NewHaveItemServer(DoubleArmAbility);
					}
					break;
				}
				case Shields:
				{
					NewHaveItemServer(Shields);
					break;
				}
				case StoneDamageBuff:
				{
					NewHaveItemServer(StoneDamageBuff);
					break;
				}
				case RadiationAntidot:
				{
					NewHaveItemServer(RadiationAntidot);
					break;
				}
				case SpeedBust:
				{
					if (LastRAbilityIndex < 2)
					{
						NewRAbility(SpeedBust);
						NewHaveItemServer(RadiationAntidot);
					}
					break;
				}
				case VentilaciaRubilnick:
				{
					if (Cast<ABP_VentilaciaRubilnick>(LastItem)->is_Avaliable) {
						UserView->E_Mark->SetVisibility(ESlateVisibility::Hidden);
						LastItem->Item->SetRenderCustomDepth(false);
						LastItem->Item->MarkRenderStateDirty();
						Cast<ABP_VentilaciaRubilnick>(LastItem)->is_Avaliable = false;
						NewHaveItemServer(VentilaciaRubilnick);
					}
					break;
				}
				case StoneDamageBuffTemp:
				{
					if (LastRAbilityIndex < 2)
					{
						NewRAbility(StoneDamageBuffTemp);
						NewHaveItemServer(StoneDamageBuffTemp);
					}
					break;
				}
				case ImmortalPotion:
				{
					if (LastRAbilityIndex < 2)
					{
						NewRAbility(ImmortalPotion);
						NewHaveItemServer(ImmortalPotion);
					}
					break;
				}
				case NasosZatichka:
				{
					NewHaveItemServer(NasosZatichka);
					break;
				}
				}
			}
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
	if (bCanWalkingAndWatching) {
		if (IsNotInWebCam) {
			IsSuccessOpening = false;
			if (Cast<AOpenArea>(LastItem))
			{
				GoToServerOpenArea(false);
			}
			UserView->StopAllAnimations();
		}
		else
		{
			TimeLine_FOV_WebCam->Reverse();
			CameraZoomOut();
		}
	}
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

void AChel::NewHaveItemServer_Implementation(int32 ItemType, int32 ReplaceItemType = -1)
{
	if (ItemType >= 0 && ItemType <= 2) {
		DoesHave[ItemType] = true;
		TArray<AActor*>Players;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AChel::StaticClass(), Players);
		for (auto& Player : Players)
			Cast<AChel>(Player)->NewHaveItemClient(ItemType);
	}

	FHitResult OutHit;

	FVector StartLocation = CameraComp->GetComponentLocation();
	FVector EndLocation = StartLocation + CameraComp->GetForwardVector() * 300;

	FCollisionQueryParams CollisionParams;

	World->LineTraceSingleByChannel(OutHit, StartLocation, EndLocation, ECC_Visibility, CollisionParams);
	if (OutHit.GetActor()) {
		APickableItem* TempItem = Cast<APickableItem>(OutHit.GetActor());
		ADezinfectorNasosZatichka* Zatichka = Cast<ADezinfectorNasosZatichka>(OutHit.GetActor());
		if (Zatichka)
		{
			Zatichka->Interact();
		}
		if (TempItem)
		{
			ACache_Key* CacheKey = Cast<ACache_Key>(TempItem);
			if (CacheKey)
			{
				UE_LOG(LogTemp, Warning, TEXT("Lalala"));
				CacheKey->RemoveAndRefreshTimer();
			}
			else
			{
				switch (TempItem->Type)
				{
				case 0:
				{
					if (GS->CurrentBoltorez == 1)
					{
						int ArrayIndex = FMath::Rand() % GS->CacheItems_Stuff_IsAvaliable.Num();
						while (!GS->CacheItems_Stuff_IsAvaliable[ArrayIndex])
						{
							ArrayIndex = FMath::Rand() % GS->CacheItems_Stuff_IsAvaliable.Num();
						}
						FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
						TempItem->AttachToActor(GS->Caches[ArrayIndex], AttachmentRules);
						TempItem->SetActorScale3D(GS->BoltorezTransform[GS->Caches[ArrayIndex]->CacheIndex].GetScale3D());
						FVector NewLocation;
						NewLocation.X = GS->BoltorezTransform[GS->Caches[ArrayIndex]->CacheIndex].GetLocation().X / abs(GS->Caches[ArrayIndex]->GetActorScale3D().X);
						NewLocation.Y = GS->BoltorezTransform[GS->Caches[ArrayIndex]->CacheIndex].GetLocation().Y / abs(GS->Caches[ArrayIndex]->GetActorScale3D().Y);
						NewLocation.Z = GS->BoltorezTransform[GS->Caches[ArrayIndex]->CacheIndex].GetLocation().Z / abs(GS->Caches[ArrayIndex]->GetActorScale3D().Z);
						TempItem->SetActorRelativeLocation({ 0.0f, 0.0f, 0.0f });
						TempItem->SetActorRelativeRotation({ 0.0f, 0.0f, 0.0f });
						TempItem->AddActorLocalOffset(NewLocation);
						TempItem->AddActorLocalRotation(GS->BoltorezTransform[GS->Caches[ArrayIndex]->CacheIndex].GetRotation());
						GS->CacheItems_Stuff_IsAvaliable[TempItem->EnabledArrayIndex] = true;
						Cast<APickableItem>(TempItem)->EnabledArrayIndex = ArrayIndex;
						GS->CacheItems_Stuff_IsAvaliable[ArrayIndex] = false;
					}
					else
					{
						GS->CurrentBoltorez--;
						GS->CacheItems_Stuff_IsAvaliable[TempItem->EnabledArrayIndex] = true;
						TempItem->Destroy();
					}
					break;
				}
				case 1:
				{
					if (GS->CurrentKeyShelter == 1)
					{
						int ArrayIndex = FMath::Rand() % GS->CacheItems_Stuff_IsAvaliable.Num();
						while (!GS->CacheItems_Stuff_IsAvaliable[ArrayIndex])
						{
							ArrayIndex = FMath::Rand() % GS->CacheItems_Stuff_IsAvaliable.Num();
						}
						FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
						TempItem->AttachToActor(GS->Caches[ArrayIndex], AttachmentRules);
						TempItem->SetActorScale3D(GS->KeyShelterTransform[GS->Caches[ArrayIndex]->CacheIndex].GetScale3D());
						FVector NewLocation;
						NewLocation.X = GS->KeyShelterTransform[GS->Caches[ArrayIndex]->CacheIndex].GetLocation().X / abs(GS->Caches[ArrayIndex]->GetActorScale3D().X);
						NewLocation.Y = GS->KeyShelterTransform[GS->Caches[ArrayIndex]->CacheIndex].GetLocation().Y / abs(GS->Caches[ArrayIndex]->GetActorScale3D().Y);
						NewLocation.Z = GS->KeyShelterTransform[GS->Caches[ArrayIndex]->CacheIndex].GetLocation().Z / abs(GS->Caches[ArrayIndex]->GetActorScale3D().Z);
						TempItem->SetActorRelativeLocation({ 0.0f, 0.0f, 0.0f });
						TempItem->SetActorRelativeRotation({ 0.0f, 0.0f, 0.0f });
						TempItem->AddActorLocalOffset(NewLocation);
						TempItem->AddActorLocalRotation(GS->KeyShelterTransform[GS->Caches[ArrayIndex]->CacheIndex].GetRotation());
						GS->CacheItems_Stuff_IsAvaliable[TempItem->EnabledArrayIndex] = true;
						Cast<APickableItem>(TempItem)->EnabledArrayIndex = ArrayIndex;
						GS->CacheItems_Stuff_IsAvaliable[ArrayIndex] = false;
					}
					else
					{
						GS->CurrentKeyShelter--;
						GS->CacheItems_Stuff_IsAvaliable[TempItem->EnabledArrayIndex] = true;
						TempItem->Destroy();
					}
					break;
				}
				case 2:
				{
					if (GS->CurrentOtvertka == 1)
					{
						int ArrayIndex = FMath::Rand() % GS->CacheItems_Stuff_IsAvaliable.Num();
						while (!GS->CacheItems_Stuff_IsAvaliable[ArrayIndex])
						{
							ArrayIndex = FMath::Rand() % GS->CacheItems_Stuff_IsAvaliable.Num();
						}
						FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
						TempItem->AttachToActor(GS->Caches[ArrayIndex], AttachmentRules);
						TempItem->SetActorScale3D(GS->OtvertkaTransform[GS->Caches[ArrayIndex]->CacheIndex].GetScale3D());
						FVector NewLocation;
						NewLocation.X = GS->OtvertkaTransform[GS->Caches[ArrayIndex]->CacheIndex].GetLocation().X / abs(GS->Caches[ArrayIndex]->GetActorScale3D().X);
						NewLocation.Y = GS->OtvertkaTransform[GS->Caches[ArrayIndex]->CacheIndex].GetLocation().Y / abs(GS->Caches[ArrayIndex]->GetActorScale3D().Y);
						NewLocation.Z = GS->OtvertkaTransform[GS->Caches[ArrayIndex]->CacheIndex].GetLocation().Z / abs(GS->Caches[ArrayIndex]->GetActorScale3D().Z);
						TempItem->SetActorRelativeLocation({ 0.0f, 0.0f, 0.0f });
						TempItem->SetActorRelativeRotation({ 0.0f, 0.0f, 0.0f });
						TempItem->AddActorLocalOffset(NewLocation);
						TempItem->AddActorLocalRotation(GS->OtvertkaTransform[GS->Caches[ArrayIndex]->CacheIndex].GetRotation());
						GS->CacheItems_Stuff_IsAvaliable[TempItem->EnabledArrayIndex] = true;
						Cast<APickableItem>(TempItem)->EnabledArrayIndex = ArrayIndex;
						GS->CacheItems_Stuff_IsAvaliable[ArrayIndex] = false;
					}
					else
					{
						GS->CurrentOtvertka--;
						GS->CacheItems_Stuff_IsAvaliable[TempItem->EnabledArrayIndex] = true;
						TempItem->Destroy();
					}
					break;
				}
				case AmmoBackPack:
				{
					MaxAmmoCount += 5;
					TempItem->Destroy();
					break;
				}
				case RentgenGlasses:
				{
					ReplaceQAbilityItem(ReplaceItemType, TempItem->EnabledArrayIndex);
					TempItem->Destroy();
					break;
				}
				case ChelsDetector:
				{
					ReplaceQAbilityItem(ReplaceItemType, TempItem->EnabledArrayIndex);
					TempItem->Destroy();
					break;
				}
				case HealthPacket:
				{
					TempItem->Destroy();
					break;
				}
				case DoubleArmAbility:
				{
					TempItem->Destroy();
					break;
				}
				case Shields:
				{
					ShieldsCount++;
					TempItem->Destroy();
					break;
				}
				case StoneDamageBuff:
				{
					StoneDamageBuffCount++;
					TempItem->Destroy();
					break;
				}
				case RadiationAntidot:
				{
					DoesRadiationAntidot = 0;
					TempItem->Destroy();
					break;
				}
				case SpeedBust:
				{
					TempItem->Destroy();
					break;
				}
				case VentilaciaRubilnick:
				{
					ABP_VentilaciaRubilnick* Rubilnick = Cast<ABP_VentilaciaRubilnick>(TempItem);
					Rubilnick->CheckVentilaciaAvaliable();
					break;
				}
				case StoneDamageBuffTemp:
				{
					TempItem->Destroy();
					break;
				}
				case ImmortalPotion:
				{
					TempItem->Destroy();
					break;
				}
				}
			}
		}
	}
}

void AChel::ReplaceQAbilityItem(int32 Type, int32 ItemIndex)
{
	if (Type == -1)
		return;
	TSubclassOf<APickableItem> ReplaceClass;
	FVector NewLocation;
	FVector NewScale;
	FRotator NewRotation;
	switch (Type)
	{
	case ChelsDetector:
	{
		ReplaceClass = GS->ChelDetector_class;

		NewLocation.X = GS->ChelDetectorTransform[GS->Caches[ItemIndex]->CacheIndex].GetLocation().X / abs(GS->Caches[ItemIndex]->GetActorScale3D().X);
		NewLocation.Y = GS->ChelDetectorTransform[GS->Caches[ItemIndex]->CacheIndex].GetLocation().Y / abs(GS->Caches[ItemIndex]->GetActorScale3D().Y);
		NewLocation.Z = GS->ChelDetectorTransform[GS->Caches[ItemIndex]->CacheIndex].GetLocation().Z / abs(GS->Caches[ItemIndex]->GetActorScale3D().Z);

		NewRotation = FRotator(GS->ChelDetectorTransform[GS->Caches[ItemIndex]->CacheIndex].GetRotation());
		NewScale = GS->ChelDetectorTransform[GS->Caches[ItemIndex]->CacheIndex].GetScale3D();
		break;
	}
	case RentgenGlasses:
	{
		ReplaceClass = GS->RentgenGlass_class;

		NewLocation.X = GS->RentgenGlassTransform[GS->Caches[ItemIndex]->CacheIndex].GetLocation().X / abs(GS->Caches[ItemIndex]->GetActorScale3D().X);
		NewLocation.Y = GS->RentgenGlassTransform[GS->Caches[ItemIndex]->CacheIndex].GetLocation().Y / abs(GS->Caches[ItemIndex]->GetActorScale3D().Y);
		NewLocation.Z = GS->RentgenGlassTransform[GS->Caches[ItemIndex]->CacheIndex].GetLocation().Z / abs(GS->Caches[ItemIndex]->GetActorScale3D().Z);

		NewRotation = FRotator(GS->RentgenGlassTransform[GS->Caches[ItemIndex]->CacheIndex].GetRotation());
		NewScale = GS->RentgenGlassTransform[GS->Caches[ItemIndex]->CacheIndex].GetScale3D();
		break;
	}
	}

	AActor* NewItem = GetWorld()->SpawnActor<AActor>(ReplaceClass);
	FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
	NewItem->AttachToActor(GS->Caches[ItemIndex], AttachmentRules);
	NewItem->SetActorScale3D(NewScale);
	NewItem->AddActorLocalOffset(NewLocation);
	NewItem->AddActorLocalRotation(NewRotation);
	Cast<APickableItem>(NewItem)->EnabledArrayIndex = ItemIndex;
	GS->CacheItems_Stuff_IsAvaliable[ItemIndex] = false;
}

bool AChel::NewHaveItemServer_Validate(int32 ItemType, int32 ReplaceItemType = -1)
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

void AChel::StoneAttack(int StoneIndex, float StoneDamage)
{
	if (IsInGame) 
	{
		Health += StoneDamage / (1 + 0.2 * ShieldsCount) * DoesNotImmortal;
		if (Health + DeltaRadiation >= 1.0f)
		{
			KillerIndex = StoneIndex;
		}

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
			for (auto& Player : Players)
					Cast<AChel>(Player)->RefreshWidgets(DoesHave, KillerIndex, Index);
			DoesHave.Init(false, 3);
			bCanWalkingAndWatching = true;
			KillPlayer();
		}
	}
}

void AChel::RefreshWidgets_Implementation(const TArray<bool>& whatToUpdate, int KillerNickIndex, int VictimNickIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("WidgetUpdates"))
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

	if (KillerNickIndex == -1) {
		UPlayerSuicide* PS_Widget = Cast<UPlayerSuicide>(CreateWidget(World, PlayerSuicide_class));
		PS_Widget->Player->SetText(GS->NickNames[VictimNickIndex]);
		KillFeed->VB_KillFeed->AddChild(PS_Widget);
	}
	else
	{
		UPlayerKillPlayer* PKP_Widget = Cast<UPlayerKillPlayer>(CreateWidget(World, PlayerKillPlayer_class));
		PKP_Widget->Killer->SetText(GS->NickNames[KillerNickIndex]);
		PKP_Widget->Victim->SetText(GS->NickNames[VictimNickIndex]);
		KillFeed->VB_KillFeed->AddChild(PKP_Widget);
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

		KillFeed->VB_KillFeed->AddChild(PLI_Widget);
	}

}

void AChel::KillPlayer()
{
	TArray<AActor*>Players;
	UGameplayStatics::GetAllActorsOfClass(World, AChel::StaticClass(), Players);

	DropCoreItems();

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
	if (Widget_Note)
		Widget_Note->SetVisibility(ESlateVisibility::Hidden);
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
	ShowStoneMulticast();
	SetActorHiddenInGame(false);
	IsNotInWebCam = true;
	IsInGame = true;
	Health = 0;
	Ammo = MaxAmmoCount;

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
	if (EscapeWay != 1) {
		GS->Areas[EscapeWay]->GetOverlappingActors(Chels);
		for (auto& Player : Chels)
		{
			Cast<AChel>(Player)->ExitAvaliableUpdate(EscapeWay);
		}
	}
	else {
		GS->Areas[3]->GetOverlappingActors(Chels);
		for (auto& Player : Chels)
		{
			Cast<AChel>(Player)->ExitAvaliableUpdate(ShelterOpener);
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
	DoesHave[EscapeWay] = false;
	TArray<AActor*>DeletingItems;
	switch (EscapeWay)
	{
	case Boltorez:
	{
		UGameplayStatics::GetAllActorsOfClass(World, GS->Boltorez, DeletingItems);
		break;
	}
	case KeyShelter:
	{
		UGameplayStatics::GetAllActorsOfClass(World, GS->KeyShelter, DeletingItems);
		break;
	}
	case Otvertka:
	{
		UGameplayStatics::GetAllActorsOfClass(World, GS->Otvertka, DeletingItems);
		break;
	}
	}

	for (auto& it : DeletingItems)
	{
		it->Destroy();
	}
}

bool AChel::StuffAvaliableUpdate_Validate(int32 EscapeWay)
{
	return true;
}

void AChel::ExitAvaliableUpdate_Implementation(int32 EscapeWay)
{
	AreaCode = EscapeWay;
	UserView->EscapeText->SetVisibility(ESlateVisibility::Visible);
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

		TArray<AActor*>Chelix;
		GenAreaObj->ShelterCollision->Collision->GetOverlappingActors(Chelix, AChel::StaticClass());
		for (auto& it : Chelix)
		{
			Cast<AChel>(it)->ShowUIAfterTerminalAndGenerator(1, true);
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
			Cast<AChel>(it)->ChangeCorretca_Client(0);
		}
		GS->EventSpawnNote();
	}
	else {
		TArray<AActor*> Players;
		GenAreaObj->GetOverlappingActors(Players, AChel::StaticClass());
		for (auto& it: Players) {
			Cast<AChel>(it)->ChangeCorretca_Client(GenAreaObj->Stadiya);
		}
	}
}

bool AChel::ChangeGeneratorStas_Validate()
{
	return true;
}

void AChel::CallDoThomethinkArea_Implementation()
{
	Cast<AOpenArea>(LastItem)->DoSomethink();
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
	UserView->AddDoubleRadiationEffect();
}

void AChel::DisableDoubleRadiationWidget_Implementation()
{
	UserView->DisableDoubleRadiationEffect();
}

void AChel::ChangeCorretca_Client_Implementation(int32 ValueV)
{
	ChangeCorretcaPosition(ValueV);
}

void AChel::HideWidgetStas_Implementation()
{
	UserView->AreaUsedText->SetVisibility(ESlateVisibility::Visible);
	GeneratorView->SetVisibility(ESlateVisibility::Hidden);
	TickEnableGeneratorWidget = false;
}

void AChel::ChangeButtonCount_Server_Implementation()
{
	FHitResult OutHit;

	FVector StartLocation = CameraComp->GetComponentLocation();
	FVector EndLocation = StartLocation + CameraComp->GetForwardVector() * 300;

	FCollisionQueryParams CollisionParams;

	World->LineTraceSingleByChannel(OutHit, StartLocation, EndLocation, ECC_Visibility, CollisionParams);
	if (OutHit.GetActor()) {
		AButtonCanalization* TempItem = Cast<AButtonCanalization>(OutHit.GetActor());
		if (TempItem)
		{
			if (!TempItem->DoesRefresh)
			{
				TempItem->Open();
				GS->CurrentButtonCount++;
				if (GS->CurrentButtonCount == 3)
				{
					TArray<AActor*>CanalAreas;
					UGameplayStatics::GetAllActorsOfClass(World, ACanalizationDamageCollision::StaticClass(), CanalAreas);
					if (CanalAreas.Num() != 0)
					{
						Cast<ACanalizationDamageCollision>(CanalAreas[0])->StopRadiation();
					}
				}
			}
		}
	}
}

bool AChel::ChangeButtonCount_Server_Validate()
{
	return true;
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
	TArray<AActor*> Items;
	UGameplayStatics::GetAllActorsOfClass(World, APickableItem::StaticClass(), Items);
	TArray<APickableItem*> ImportantItems;
	ImportantItems.Init(nullptr, 0);
	for (auto& it : Items) 
	{
		if (Cast<APickableItem>(it)->Type <= 2) 
		{
			ImportantItems.Add(Cast<APickableItem>(it));
		}
	}
	if (ImportantItems.Num() != 0)
	{
		LastOutlineItem = ImportantItems[FMath::Rand() % ImportantItems.Num()];
		LastOutlineItem->Item->SetRenderCustomDepth(true);
		LastOutlineItem->Item->SetCustomDepthStencilValue(2);
		LastOutlineItem->Item->MarkRenderStateDirty();
		AddTargetArrowDynamic(LastOutlineItem);

		FTimerHandle FuzeTimerHandle;
		World->GetTimerManager().SetTimer(FuzeTimerHandle, this, &AChel::HideRandomItem, ShowRandomItem_TIME, false);

	}
}

void AChel::HideRandomItem() {
	if (LastOutlineItem) 
	{
		LastOutlineItem->Item->SetRenderCustomDepth(false);
		LastOutlineItem->Item->MarkRenderStateDirty();
		LastOutlineItem = nullptr;
		RemoveTargetArrowDynamic();
	}
}

void AChel::ShowNoiseWebCamUI_Implementation(bool DoesNoise)
{
	ShowNoiseBlueprint(DoesNoise);
}

void AChel::LockWebCam_Server_Implementation()
{
	FHitResult OutHit;

	FVector StartLocation = CameraComp->GetComponentLocation();
	FVector EndLocation = StartLocation + CameraComp->GetForwardVector() * 300;

	FCollisionQueryParams CollisionParams;

	World->LineTraceSingleByChannel(OutHit, StartLocation, EndLocation, ECC_Visibility, CollisionParams);
	if (OutHit.GetActor()) {
		AWebCamLocker* TempItem = Cast<AWebCamLocker>(OutHit.GetActor());
		if (TempItem)
		{
			if (TempItem->DoesLock && !TempItem->DoesPlayAnim)
			{
				TempItem->Close();
				TempItem->DoesLock = false;
				if (GS->WebCams[TempItem->Index]->is_Enabled == true)
				{
					GS->WebCams[TempItem->Index]->CurChelix->ShowNoiseWebCamUI(false);
				}
				GS->WebCams[TempItem->Index]->is_Enabled = true;
			}
			else if (!TempItem->DoesLock && !TempItem->DoesPlayAnim)
			{
				TempItem->Open();
				TempItem->DoesLock = true;
				if (GS->WebCams[TempItem->Index]->is_Enabled == false)
				{
					GS->WebCams[TempItem->Index]->CurChelix->ShowNoiseWebCamUI(true);
				}
				GS->WebCams[TempItem->Index]->is_Enabled = false;
			} 
		}
	}
}

bool AChel::LockWebCam_Server_Validate()
{
	return true;
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
	UserView->AreaUsedText->SetVisibility(ESlateVisibility::Hidden);
	UserView->HoldText->SetVisibility(ESlateVisibility::Visible);
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

void AChel::ButtonPressAnimationServer_Implementation() {
	FHitResult OutHit;

	FVector StartLocation = CameraComp->GetComponentLocation();
	FVector EndLocation = StartLocation + CameraComp->GetForwardVector() * 300;

	FCollisionQueryParams CollisionParams;

	if (World->LineTraceSingleByChannel(OutHit, StartLocation, EndLocation, ECC_Visibility, CollisionParams))
	{		
		Cast<AClickButton>(OutHit.GetActor())->ButtonPressAnimation();
	}
	
}

bool AChel::ButtonPressAnimationServer_Validate()
{
	return true;
}

void AChel::DoTraceOpenArea() 
{
	FHitResult OutHit;

	FVector StartLocation = CameraComp->GetComponentLocation();
	FVector EndLocation = StartLocation + CameraComp->GetForwardVector() * 300;

	FCollisionQueryParams CollisionParams;

	if (World->LineTraceSingleByChannel(OutHit, StartLocation, EndLocation, ECC_Visibility, CollisionParams))
	{
		LastItem = Cast<AOpenArea>(OutHit.GetActor());
	}

}

void AChel::GoToServerOpenArea_Implementation(bool IsStart) 
{
	if (IsStart) 
	{
		DoTraceOpenArea();
		AOpenArea* CurArea = Cast<AOpenArea>(LastItem);
		CurArea->bIsUsed = true;
		CurArea->RotateVentilServer();
	}
	else
	{
		AOpenArea* CurArea = Cast<AOpenArea>(LastItem);
		if (CurArea) {
			CurArea->bIsUsed = false;
			if (Cast<AOpenArea>(LastItem)->CurTimeVentil != 10.f)
			{
				Cast<AOpenArea>(LastItem)->RotateVentilServerReverse();
			}
			LastItem = nullptr;
		}
	}
}

bool AChel::GoToServerOpenArea_Validate(bool IsStart)
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
		AreaCode = NewAreaType;
		if (!GS->AreaAvaliables[NewAreaType])
		{
			if (DoesHave[NewAreaType])
				UserView->HoldText->SetVisibility(ESlateVisibility::Visible);
		}
	}
	else
	{
		AreaCode = -1;
		UserView->HoldText->SetVisibility(ESlateVisibility::Hidden);
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

void AChel::AddStoneDamageBuffTemp_Implementation()
{
	StoneDamageBuffTempValue = 2.0f;
	CurrentStoneDamageBuffTempCount++;
	FTimerHandle FuzeTimerHandle2;
	GetWorld()->GetTimerManager().SetTimer(FuzeTimerHandle2, this, &AChel::RemoveStoneDamageBuffTemp, 10, false);
}

bool AChel::AddStoneDamageBuffTemp_Validate()
{
	return true;
}

void AChel::RemoveStoneDamageBuffTemp()
{
	CurrentStoneDamageBuffTempCount--;
	if (CurrentStoneDamageBuffTempCount == 0)
	{
		StoneDamageBuffTempValue = 1.0f;
	}
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
	RAbilityPanel[RAbilityTypeIndex]->Count--;
	RAbilityPanel[RAbilityTypeIndex]->CountText->SetText(FText::AsNumber(RAbilityPanel[LastRAbilityIndex]->Count));
	if (RAbilityPanel[RAbilityTypeIndex]->Count == 0)
	{
		LastRAbilityIndex = RAbilityTypeIndex - 1;
		for (int i = RAbilityTypeIndex + 1; i < RAbilityPanel.Num(); i++)
		{
			if (RAbilityPanel[i]->Count > 0) 
			{
				RAbilityPanel[i - 1]->Count = RAbilityPanel[i]->Count;
				RAbilityPanel[i - 1]->AbilityType = RAbilityPanel[i]->AbilityType;
				RAbilityPanel[i - 1]->AbilityImage->SetBrush(RAbilityPanel[i]->AbilityImage->Brush);
				RAbilityPanel[i - 1]->CountText->SetText(FText::AsNumber(RAbilityPanel[i - 1]->Count));
				RAbilityPanel[i - 1]->InArrayIndex = i - 1;
				LastRAbilityIndex++;
			}
		}
		if (LastRAbilityIndex < (RAbilityPanel.Num() - 1))
		{
			RAbilityPanel[LastRAbilityIndex + 1]->Count = 0;
		}
		if (LastRAbilityIndex < RAbilityTypeIndex)
		{
			RAbilityTypeIndex = LastRAbilityIndex;
			SetCurRAbilityUserView();
		}
		RAbilityPanel[LastRAbilityIndex + 1]->SetVisibility(ESlateVisibility::Hidden);
	}
}

bool AChel::NewRAbility(TSubclassOf<UConsumableAbility>& Ability_class)
{
	if (LastRAbilityIndex == -1)
	{
		RAbilityTypeIndex = 0;
	}
	if (LastRAbilityIndex != 2)
	{
		for (int i = 0; i < RAbilityPanel.Num(); i++)
		{
			if (RAbilityPanel[LastRAbilityIndex]) {
				if (RAbilityPanel[LastRAbilityIndex]->StaticClass() == Ability_class)
				{
					if (RAbilityPanel[LastRAbilityIndex]->CurCount + 1 <= RAbilityPanel[LastRAbilityIndex]->MaxCountToStack)
					{
						RAbilityPanel[LastRAbilityIndex]->CurCount++;
						RAbilityPanel[LastRAbilityIndex]->UpdateCount();
						return true;
					}
					else
					{
						LastRAbilityIndex++;
						RAbilityPanel[LastRAbilityIndex] = NewObject<UConsumableAbility>(Ability_class);
						RAbilityPanel[LastRAbilityIndex]->UserViewSlot = Cast<URAbilitySlot>(MyInventory->RAbilityPanel->GetChildAt(LastRAbilityIndex));
						RAbilityPanel[LastRAbilityIndex]->SetAbilityToSlot();
					}
				}
			}
		}

		if (LastRAbilityIndex == 0)
		{
			SetCurRAbilityUserView();
		}
		return true;
	}
	return false;
}

void AChel::SetCurRAbilityUserView()
{
	if (RAbilityTypeIndex != -1) {
		UserView->CurRSlot->AbilityImage->SetBrush(RAbilityPanel[RAbilityTypeIndex]->AbilityImage->Brush);
		UserView->CurRSlot->CountText->SetText(FText::AsNumber(RAbilityPanel[RAbilityTypeIndex]->Count));
	}
	else
	{
		//FSlateBrush NewBrush = Дефолтная картинка для R Способности;
		//UserView->CurRSlot->AbilityImage->SetBrush(NewBrush);
		UserView->CurRSlot->CountText->SetText(FText::AsNumber(0));
	}
}

void AChel::DropCoreItems()
{
	if (DoesHave[0]) {
		FTransform Trsfrm;
		Trsfrm.SetLocation(DamageCollision->GetComponentLocation());
		Trsfrm.SetRotation(FQuat(FRotator(DamageCollision->GetComponentRotation())));
		Trsfrm.SetScale3D(FVector(1.0f, 1.0f, 1.0f));
		ACoreItem* DroppedItm = World->SpawnActor<ACoreItem>(GS->Boltorez, Trsfrm);
		DroppedItm->Collision->SetPhysicsLinearVelocity(FVector(CameraComp->GetForwardVector() * 200.f));
	}
	if (DoesHave[1]) {
		FTransform Trsfrm;
		Trsfrm.SetLocation(DamageCollision->GetComponentLocation());
		Trsfrm.SetRotation(FQuat(FRotator(DamageCollision->GetComponentRotation())));
		Trsfrm.SetScale3D(FVector(1.0f, 1.0f, 1.0f));
		ACoreItem* DroppedItm = World->SpawnActor<ACoreItem>(GS->KeyShelter, Trsfrm);
		DroppedItm->Collision->SetPhysicsLinearVelocity(FVector(CameraComp->GetForwardVector() * 200.f));
	}
	if (DoesHave[2]) {
		FTransform Trsfrm;
		Trsfrm.SetLocation(DamageCollision->GetComponentLocation());
		Trsfrm.SetRotation(FQuat(FRotator(DamageCollision->GetComponentRotation())));
		Trsfrm.SetScale3D(FVector(1.0f, 1.0f, 1.0f));
		ACoreItem* DroppedItm = World->SpawnActor<ACoreItem>(GS->Otvertka, Trsfrm);
		DroppedItm->Collision->SetPhysicsLinearVelocity(FVector(CameraComp->GetForwardVector() * 200.f));
	}
}

void AChel::SetWeaponToSlot(int32 IndexWeapon) //вызывается из мультикастового события
{
	CurrentWeapons[IndexWeapon]->GunMesh->SetVisibility(true);
	CurrentWeapons[(IndexWeapon + 1) % 2]->GunMesh->SetVisibility(false);
	CurrentIndex = IndexWeapon;
	if (IsPlayerOwner) {
		RefreshWidgetAmmoOwning(CurrentWeapons[CurrentIndex]->LeftAmmo, CurrentWeapons[CurrentIndex]->MaxAmmo, CurrentIndex);
	}
}

void AChel::SwitchToFreeWeapon() {
	if (CurrentWeapons[0]->LeftAmmo == 0) {
		if (CurrentWeapons[1]->LeftAmmo == 0) {
			CurrentIndex = 0;
			if (IsPlayerOwner) {
				ClearWeaponInfo();
			}
		}
		else {
			SetWeaponToSlot(1);
		}
	}
	else {
		SetWeaponToSlot(0);
	}
}
void AChel::RefreshWidgetAmmoOwning(int32 NewLeftAmmo, int32 NewMaxAmmo, int32 NewCurIndex) {
	CurrentIndex = NewCurIndex;
	UserView->AmmoLabel->SetVisibility(ESlateVisibility::Visible);
	UserView->AmmoMax->SetVisibility(ESlateVisibility::Visible);
	UserView->AmmoLabel->SetText(FText::AsNumber(CurrentWeapons[CurrentIndex]->LeftAmmo));
	UserView->AmmoLabel->SetText(FText::AsNumber(CurrentWeapons[CurrentIndex]->LeftAmmo));
}

void AChel::RefreshWidgetAmmoOwningClient_Implementation(int32 NewLeftAmmo, int32 NewMaxAmmo, int32 NewCurIndex)
{
	RefreshWidgetAmmoOwning(NewLeftAmmo, NewMaxAmmo, NewCurIndex);
}

void AChel::SetWeaponToSlotMulticast_Implementation(int32 IndexWeapon)
{
	SetWeaponToSlot(IndexWeapon);
}
void AChel::ChangeAmmoOwner_Implementation(int32 NewLeftAmmo)
{
	CurrentWeapons[CurrentIndex]->LeftAmmo = NewLeftAmmo;
}
void AChel::StartAnimInCurSlot_Implementation()
{
	if (IsPlayerOwner) {
		CanFireWeapon = false;
	}
	CurrentWeapons[CurrentIndex]->AnimationThrow();
}

void AChel::StartAnimInCurSlotReverse_Implementation(bool HaveAmmo)
{
	int32 idx = CurrentIndex; //на случай, еслы мы вызовем switchToFreeWeapon
	if (!HaveAmmo) {
		if (IsPlayerOwner) {
			CanFireWeapon = true;
		}
		
		CurrentWeapons[CurrentIndex]->GunMesh->SetVisibility(false);
		SwitchToFreeWeapon();
	}
	CurrentWeapons[idx]->AnimationThrowReverse();

}
void AChel::ClearWeaponInfo() {
	UserView->AmmoLabel->SetVisibility(ESlateVisibility::Hidden);
	UserView->AmmoMax->SetVisibility(ESlateVisibility::Hidden);
}

void AChel::ClearWeaponInfoClient_Implementation() {
	ClearWeaponInfo();
}

