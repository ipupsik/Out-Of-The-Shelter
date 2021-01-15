// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/KismetMathLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "UI/RAbilitySlot.h"
#include "UI/KDA_Stat.h"
#include "Spectator.h"
#include "FinalMenuPawn.h"
#include "AmmoPoint.h"
#include "Cache.h"
#include "GeneratorArea.h"
#include "UI/GeneratorWidget.h"
#include "ButtonCanalization.h"
#include "WebCamLocker.h"
#include "ClickButton.h"
#include "UI/KillFeed.h"
#include "UI/Tab.h"
#include "Components/SceneComponent.h"
#include "ItemPromtArrow_MainExis.h"
#include "GI.h"
#include "GS.h"
#include "Stone.h"
#include "PickableItem.h"
#include "OpenArea.h"
#include "UI/UserView.h"
#include "UI/PlayerKillPlayer.h"
#include "UI/WebCamWidget.h"
#include "UI/PlayerLostItem.h"
#include "UI/PlayerSuicide.h"
#include "UI/GeneratorWidget.h"
#include "Components/TimelineComponent.h"
#include "UI/NoteWidget.h"
#include "UI/Inventory.h"
#include "UI/TargetArrow.h"
#include "Components/CapsuleComponent.h"

#include "Chel.generated.h"

class UCameraComponent;
class UPoseableMeshComponent;
class UStaticMeshComponent;
class UUserWidget;

UCLASS()
class MYPROJECT9_API AChel : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AChel();

protected:
	// Called when the game starts or when spawned
	// Axis functions
	virtual void BeginPlay() override;
	void MyBeginPlay();
	void GoForward(float);
	void GoRight(float);
	void LookUp(float);
	void LookRight(float);
	void QAbilityEnable();
	void QAbilityDisable();
	void RAbilityEnable();
	void RAbilityDisable();
	// Actions functions
	void MyJump();
	void StartSprint();
	void StopSprint();

	void EnableRentgen();
	void DisableRentgen();
	void EnableChelDetector();
	void DisableChelDetector();

	void StopUseSpeedBust();

	void ThrowStoneLeft();
	void ThrowStoneRight();
	void PickUp();
	void PickUp_Released();
	void OpenAreaPressed();
	void OpenAreaReleased();

	void UpdateSpectating_Left();
	void UpdateSpectating_Right();

	UFUNCTION(Server, Reliable, WithValidation)
		void UpdateSpectating_Left_Server();
	UFUNCTION(Server, Reliable, WithValidation)
		void UpdateSpectating_Right_Server();
public:
	void ShowInventory();
	void UnShowInventory();
	void SpawnPlayer();
	void PossessedBy(AController* NewController) override;
	void UseRAbility();
	bool NewRAbility(int32 NewAbility);

	void UpdateTargetArrowPosition(AActor* TargetObj, UTargetArrow* ArrowWidget); //обновл€ем позицию стрелки-подсказки на экране
	void AddTargetArrowStatic(AActor* TargetObj); //добавл€ет стрелку-подсказку на экран(стрелка прикрепл€етс€ к определенному объекту)
	void RemoveTargetArrowStatic(AActor* TargetObj); //убирает стрелку-подсказку на экране(стрелка убираетс€ по определенному объекту)
	void AddTargetArrowDynamic(AActor* TargetObj); //добавл€ет стрелку-подсказку на экран(стрелка прикрепл€етс€ к определенному объекту)
	void RemoveTargetArrowDynamic(); //убирает стрелку-подсказку на экране
	void RemoveTargetArrowDynamic(UTargetArrow* ArrowObj); //убирает стрелку-подсказку на экране(po etoi strelke-podskazke)

	UFUNCTION(Client, Reliable)
		void DeleteStrelkaBadOutline_Client(int32 ChelIndex);
	void RemoveArrowBadOutline(int32 ChelIndex); //убирает стрелку-подсказку на экране, котора€ указывает на плохо обведенного чела(который щас подох)


	UFUNCTION(Server, Reliable, WithValidation)
		void ButtonPressAnimationServer();

	UFUNCTION(Server, Reliable, WithValidation)
		void StartSprint_Server();
	UFUNCTION(Server, Reliable, WithValidation)
		void StopSprint_Server();

	UFUNCTION(Server, Reliable, WithValidation)
		void AddNumToTerminalServer(int32 ButtonType);
	UFUNCTION(Server, Reliable, WithValidation)
		void DeleteLAstNumServer();
	UFUNCTION(Server, Reliable, WithValidation)
		void CheckCodeServer();
	UFUNCTION(Server, Reliable, WithValidation)
		void AddStoneDamageBuffTemp();

	void RemoveStoneDamageBuffTemp();

	UFUNCTION(Client, Reliable)
		void RefreshGeneratorArea();

	UFUNCTION(Client, Reliable)
		void StoneCountUpdate(int32 Count);

	UFUNCTION(NetMulticast, Reliable)
		void DisableCollisionEverywhere();

	UFUNCTION(NetMulticast, Reliable)
		void EnableCollisionEverywhere();

	UFUNCTION(Client, Reliable)
		void PlaySpawnAnimationSleep();
	UFUNCTION(Client, Reliable)
		void PlaySpawnAnimationAwake();
	//MeshComponentReplication
	UFUNCTION(NetMulticast, Reliable)
		void MeshCompRepMulticast(float RotationRoll);

	UFUNCTION(Server, Reliable, WithValidation)
		void MeshCompRepServer(float RotationRoll);

	UFUNCTION(Server, Reliable, WithValidation)
		void GoToServerOpenArea(bool IsStart);

	UFUNCTION(Server, Reliable, WithValidation)
		void RAbility_HealPacket();

	void GoToWebCamServer(int32 Iterator);

	void GoToWebCam();

	UFUNCTION(Server, Reliable, WithValidation)
		void DeliverNicknameToServer(const FText& newNickName);
	//StoneThrowReplication
	UFUNCTION(Server, Reliable, WithValidation)
		void ThrowStoneServer(bool Type);

	UFUNCTION(Server, Reliable, WithValidation)
		void AddImmortalServer();
	void RemoveImmortalServer();

	UFUNCTION(NetMulticast, Reliable)
		void ThrowStoneMulticast(bool Type);

	UFUNCTION(Server, Reliable, WithValidation)
		void NewHaveItemServer(int32 ItemType, int32 ReplaceItemType = -1);

	UFUNCTION(Client, Reliable)
		void NewHaveItemClient(int32 ItemType);

	UFUNCTION(Client, Reliable)
		void DeleteGameHUD();

	UFUNCTION(Client, Reliable)
		void AddHitMarker();

	void RemoveHitMarker();

	void PossessToSpectator();

	UFUNCTION(Server, Reliable, WithValidation)
		void ChangeGeneratorStas();

	UFUNCTION(Server, Reliable, WithValidation)
		void CallDoThomethinkArea();

	UFUNCTION(Server, Reliable, WithValidation)
		void ChangeIsAvaliableCache();

	UFUNCTION(Server, Reliable, WithValidation)
		void ChangeButtonCount_Server();

	UFUNCTION(Server, Reliable, WithValidation)
		void StuffAvaliableUpdate(int32 EscapeWay);

	UFUNCTION(Server, Reliable, WithValidation)
		void PlayerEscape(int32 EscapeWay);

	UFUNCTION(Client, Reliable)
		void ShowRandomItem();

		void HideRandomItem();

	UFUNCTION(Client, Reliable)
		void ExitAvaliableUpdate(int32 EscapeWay);

	UFUNCTION(Server, Reliable, WithValidation)
		void PlayerOpenAreaUpdate(int32 EscapeWay);

	UFUNCTION(Client, Reliable)
		void ChangeCorretca_Client(int32 ValueV);

	UFUNCTION(Server, Reliable, WithValidation)
		void AddInvisibleServer();

	UFUNCTION(BlueprintImplementableEvent)
		void InvisibleEverywhere();

	UFUNCTION(BlueprintImplementableEvent)
		void CameraZoomIn();

	UFUNCTION(BlueprintImplementableEvent)
		void CameraZoomOut();

	UFUNCTION(BlueprintImplementableEvent)
		void SpawnDeadSound();
	UFUNCTION(BlueprintImplementableEvent)
		void SpawnWakeUpSound();

	UFUNCTION(BlueprintImplementableEvent)
		void GoodAttempGeneratorSound();

	UFUNCTION(BlueprintImplementableEvent)
		void ShowNoiseBlueprint(bool NewShow);

	UFUNCTION(BlueprintImplementableEvent)
		void CameraSwitch();

	UFUNCTION(BlueprintImplementableEvent)
		void PickUpSound();

	UFUNCTION(BlueprintImplementableEvent)
		void CameraTurnOff();

	UFUNCTION(BlueprintImplementableEvent)
		void AddChromaticAbberation();

	UFUNCTION(BlueprintImplementableEvent)
		void PofigKakNaz(AActor* SDJHfgActor);

	UFUNCTION(BlueprintImplementableEvent)
		void PlayStoneThrowSound();

	UFUNCTION(BlueprintImplementableEvent)
		void PlayStoneHit();

	UFUNCTION(BlueprintImplementableEvent)
		void PlayArrowSound();

	UFUNCTION(Server, Reliable, WithValidation)
		void OutlineBad_Server();

	UFUNCTION(Server, Reliable, WithValidation)
		void UseSpeedBust_Server();

	void DoTraceOpenArea();

	UFUNCTION(NetMulticast, Reliable) //легендарна€ св€зќчка
		void OutlineBad_Multicast();

	void RefreshOutline();

	void DeleteArrowDelayKeyShelter();
	void DeleteArrowDelayBoltorez();
	void DeleteArrowDelayOtvertka();

	void ReplaceQAbilityItem(int32 Type, int32 ItemIndex);

	UFUNCTION(Server, Reliable, WithValidation)
		void LockWebCam_Server();

	UFUNCTION(Client, Reliable)
		void HideNoteWidget();

	UFUNCTION(Client, Reliable)
		void HideWidgetStas();

	UFUNCTION(Client, Reliable)
		void AreaClosedUpdate(int32 EscapeWay);

	void ResetCacheKeys();

	UFUNCTION(Client, Reliable)
		void RefreshWidgets_Winner(int32 EscapeWay);

	UFUNCTION(Client, Reliable)
		void AddDoubleRadiationWidget();

	UFUNCTION(Client, Reliable)
		void DisableDoubleRadiationWidget();

	UFUNCTION(NetMulticast, Reliable)
		void HideStoneMulticast();

	UFUNCTION(NetMulticast, Reliable)
		void ShowStoneMulticast();

	UFUNCTION(NetMulticast, Reliable)
		void HideCustomItems(bool NewHide);

	UFUNCTION(Client, Reliable)
		void ShowNoiseWebCamUI(bool DoesNoise);

	UFUNCTION(Client, Reliable)
		void ShowUIAfterTerminalAndGenerator(int32 NewAreaType, bool DoesEnabled);

	UFUNCTION(Client, Reliable)
		void CreateKDAWidget(int32 PlayerIndex, const FText& newNickName);

	UFUNCTION(Client, Reliable, BlueprintCallable)
		void DeleteKDATab(int32 newPlayerIndex);

	UFUNCTION(Client, Reliable)
		void AddChromaticAbberationClient();

	UFUNCTION(Client, Reliable)
		void SetCameraRotationWebCam(float RollRot, float PitchRot, float YawRot);

	UFUNCTION(Client, Reliable)
		void RefreshWidgets(const TArray<bool> &whatToUpdate, int KillerNickIndex, int VictimNickIndex);

	UFUNCTION(Client, Reliable)
		void RefreshTabWidget(int32 VictimIndex, int32 newKillerIndex);

	UFUNCTION()
		void OnTimelineFinished_Stone_First();
	UFUNCTION()
		void OnTimelineFinished_Stone_First_Left();

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void TimelineVectorReturn_Stone(FVector value);
	UFUNCTION()
		void TimelineVectorReturn_Stone_Left(FVector value);

	UFUNCTION()
		void TimelineFloatReturn_FOV_WebCam(float value);

	UFUNCTION()
		void OnTimelineFinished_Stone_Second();
	UFUNCTION()
		void OnTimelineFinished_Stone_Second_Left();

	UFUNCTION()
		void SleepAnimation_End();

	UFUNCTION()
		void AwakeAnimation_End();

	void StoneAttack(int StoneIndex, float StoneDamage);
	void KillPlayer();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void GetLifetimeReplicatedProps(TArray < FLifetimeProperty >& OutLifetimeProps) const override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:
	//Components Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
		UCameraComponent* CameraComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
		UPoseableMeshComponent* PoseableMeshComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
		UStaticMeshComponent* StoneRight;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
		UStaticMeshComponent* StoneLeft;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
		UCapsuleComponent* DamageCollision;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
		USphereComponent* SenseCollision;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
		USceneComponent* Scene;

	UPROPERTY(EditAnywhere, Category = "Projectile")
		TSubclassOf<AStone> StoneClass;

	//HUD Class Variables
	UPROPERTY(EditAnywhere, Category = "UI HUD")
		TSubclassOf<UUserView> UserViewClass;

	void ChangeCorretcaPosition(int32 TypeChange);

	UPROPERTY(EditAnywhere, Category = "Spectator")
		TSubclassOf<ASpectator> SpectatorClass;

	UPROPERTY(EditAnywhere, Category = "UI HUD")
		TSubclassOf<UPlayerKillPlayer> PlayerKillPlayer_class;
	UPROPERTY(EditAnywhere, Category = "UI HUD")
		TSubclassOf<UPlayerSuicide> PlayerSuicide_class;
	UPROPERTY(EditAnywhere, Category = "UI HUD")
		TSubclassOf<UPlayerLostItem> PlayerLostItem_class;
	UPROPERTY(EditAnywhere, Category = "UI HUD")
		TSubclassOf<UGeneratorWidget> GeneratorView_class;
	UPROPERTY(EditAnywhere, Category = "UI HUD")
		TSubclassOf<UNoteWidget> NoteWidget_class;
	UPROPERTY(EditAnywhere, Category = "UI HUD")
		TSubclassOf<UWebCamWidget> WebCamWidget_class;
	UPROPERTY(EditAnywhere, Category = "UI HUD")
		TSubclassOf<UKDA_Stat> KDA_Stat_class;
	UPROPERTY(EditAnywhere, Category = "UI HUD")
		TSubclassOf<UTab> Tab_Stat_class;
	UPROPERTY(EditAnywhere, Category = "UI HUD")
		TSubclassOf<UInventory> Inventory_class;
	UPROPERTY(EditAnywhere, Category = "UI HUD")
		TSubclassOf<UKillFeed> KillFeed_class;
	UPROPERTY(EditAnywhere, Category = "UI HUD") //класс стрелки подсказки
		TSubclassOf<UTargetArrow> TargetArrowClass;

	//HUD Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		UUserView* UserView;
	UKillFeed* KillFeed;
	UInventory* MyInventory;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UWebCamWidget* WebCamUI;
	//GameInstance + GameState
	AGS* GS;
	UGI* GI;
	//PlayerVariables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "PlayerVariables")
		float Health;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category = "PlayerVariables")
		int Index;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category = "PlayerVariables")
		int Ammo;
	//InGameVariables
	UPROPERTY(EditAnywhere, Replicated, Category = "InGameVariables")
		bool IsInGame;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vars")
	int32 ItemCodePickUp;
	int32 AreaCode;
	UPROPERTY(Replicated)
		TArray<bool>DoesHave;
	TArray<int32>KeysCount;
	bool DoesHave_Owner;
	APickableItem* LastItem;
	ACache* LastCache;
	AButtonCanalization* LastButton;
	//GlobalSettings
	bool IsServerAuth;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool IsPlayerOwner;
	UWorld* World;
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MaxAmmoCount;
	//Settings Variables
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "Settings")
		float Sensetivity;
	UPROPERTY(EditAnywhere, Category = "Settings")
		float WebCamSensetivity;
	UPROPERTY(EditAnywhere, Category = "Settings")
		float MaxYawAngle;
	UPROPERTY(EditAnywhere, Category = "Settings")
		float MaxPitchAngle;
	UPROPERTY(EditAnywhere, Replicated, Category = "Settings")
		FText NickName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector2D ScreenPosObj;
	//TimeLine
	UTimelineComponent* TimeLine_Stone_First;
	UTimelineComponent* TimeLine_Stone_Second;

	UTimelineComponent* TimeLine_Stone_First_Left;
	UTimelineComponent* TimeLine_Stone_Second_Left;

	UTimelineComponent* TimeLine_FOV_WebCam;
	//ThrowStoneFunctions
	FOnTimelineVector InterpFunction_Stone;
	FOnTimelineVector InterpFunction_Stone_Left;
	FOnTimelineEvent TimelineFinished_Stone_First;
	FOnTimelineEvent TimelineFinished_Stone_Second;

	FOnTimelineEvent TimelineFinished_Stone_First_Left;
	FOnTimelineEvent TimelineFinished_Stone_Second_Left;

	FOnTimelineFloat InterpFunction_FOV_WebCam;

	TArray<AChel*>PlayersArray;

	//StoneAttackVars
	bool bIsAlreadyThrowing;
	bool bIsAlreadyThrowingLeft;
	UPROPERTY(EditAnywhere, Category = "Timeline")
		UCurveVector*  vCurveStone;
	UPROPERTY(EditAnywhere, Category = "Timeline")
		UCurveFloat* vCurveFOV_WebCam;
	FVector StonePositionRight;
	FVector StonePositionLeft;

	//KillFeed Vars
	int KillerIndex;

	int32 QAbilityType;
	int32 RAbilityTypeIndex;

	int32 ShieldsCount;
	int32 StoneDamageBuffCount;

	int32 DoesRadiationAntidot;
	int32 CurrentSpeedBustCount;
	float SpeedBustValue;
	float StoneDamageBuffTempValue;
	int32 CurrentStoneDamageBuffTempCount;
	int32 WebCamIterator;
	int32 DoesNotImmortal;
	int32 DoesNotImmortalCount;
	UPROPERTY(BlueprintReadWrite)
	FRotator BaseWebCamRotation;

public:
	//Logic Boolean Variables
	bool bLineTrace_is_need_refresh;
		bool bCanPossessWebCam;
	bool isTracedBad;
	UPROPERTY(BlueprintReadWrite)
		bool bCanWalkingAndWatching;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool IsNotInWebCam;
	bool CanThrowStone;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) //!!!!!!!!!!!!!!
	bool IsSuccessOpening;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) //!!!!!!!!!!!!!!
	float RadCoeff = 1; //!!!!!!!!!!!!!! (дл€ увеличени€ дамага в области газа)

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) //!!!!!!!!!!!!!!
	float MoveCoeff = 1; //!!!!!!!!!!!!!! (дл€ уменьшени€ скорости в области льда)

	float CanalizationDamage;

	bool IsAwake;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) //!!!!!!!!!!!!!!
	TArray<AActor*>CustomizationChilds;

	TArray<UTargetArrow*> TargetArrowsStatic; //массив со стрелками-подсказками на экране
	TArray<AActor*> TargetItemsStatic; //массив с предметами, к которым прив€заны стрелки-подсказки
	TArray<UTargetArrow*> TargetArrowsDynamic; //массив со стрелками-подсказками на экране
	TArray<AActor*> TargetItemsDynamic; //массив с предметами, к которым прив€заны стрелки-подсказки

	TArray<UKDA_Stat*>MyKDA_Stat;
	TArray<URAbilitySlot*>RAbilityPanel;
	FTransform MeshTrans;
	FRotator BaseRotation;

	int32 LastRAbilityIndex;

	AGeneratorArea* GenAreaObj;
	UGeneratorWidget* GeneratorView;

	APickableItem* LastOutlineItem;

	AWebCamLocker* LastWebCamLocker;

	ABP_PlayerController* MyController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNoteWidget* Widget_Note;

	AItemPromtArrow_MainExis* MainExis_Shelter;
	AItemPromtArrow_MainExis* MainExis_Ventilacia;
	AItemPromtArrow_MainExis* MainExis_Canalizacia;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bInEscMenu;
	bool TickEnableGeneratorWidget;
	bool bToRight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsRentgenRender;

	bool DoubleArmThrowing;
	bool IsAlreadyCreated;
};
