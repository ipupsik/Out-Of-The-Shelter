// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/KismetMathLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "UI/RAbilitySlot.h"
#include "UI/QAbilitySlot.h"
#include "UI/KDA_Stat.h"
#include "Spectator.h"
#include "DezinfectorNasosZatichka.h"
#include "FinalMenuPawn.h"
#include "AmmoPoint.h"
#include "Cache.h"
#include "GeneratorArea.h"
#include "UI/GeneratorWidget.h"
#include "UI/KillFeed.h"
#include "UI/Tab.h"
#include "Components/SceneComponent.h"
#include "ItemPromtArrow_MainExis.h"
#include "GI.h"
#include "GS.h"
#include "Stone.h"
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
#include "UI/VerstakWidget.h"
#include "Components/CapsuleComponent.h"
#include "QAbility.h"
#include "Chel.generated.h"

class UCameraComponent;
class UPoseableMeshComponent;
class UStaticMeshComponent;
class UUserWidget;
class AWeapon_Character;
class UConsumableAbility;
class AInteractiveItem;
class ACoreItem;

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
	void RAbilityEnable_Client();

	UFUNCTION(Server, Reliable, WithValidation)
		void RAbilityEnable_Server(const UClass* Ability_class);
	// Actions functions
	void MyJump();
	void StartSprint();
	void StopSprint();

	void EnableChelDetector();
	void DisableChelDetector();

	void StopUseSpeedBust();

	/*void ThrowStoneLeft();*/
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
	UFUNCTION(Server, Reliable, WithValidation)
		void CallEnableGasVent();
	UFUNCTION(Server, Reliable, WithValidation)
		void PickUp_Released_Server();


	void ShowInventory();
	void UnShowInventory();
	void SpawnPlayer();
	void PossessedBy(AController* NewController) override;
	void UseRAbility();
	bool NewRAbility(const UClass* Ability_class);
	void SetCurRAbilityUserView();

	void UpdateTargetArrowPosition(AActor* TargetObj, UTargetArrow* ArrowWidget); //обновляем позицию стрелки-подсказки на экране
	void AddTargetArrowStatic(AActor* TargetObj); //добавляет стрелку-подсказку на экран(стрелка прикрепляется к определенному объекту)
	void RemoveTargetArrowStatic(AActor* TargetObj); //убирает стрелку-подсказку на экране(стрелка убирается по определенному объекту)
	void AddTargetArrowDynamic(AActor* TargetObj); //добавляет стрелку-подсказку на экран(стрелка прикрепляется к определенному объекту)
	void RemoveTargetArrowDynamic(); //убирает стрелку-подсказку на экране
	void RemoveTargetArrowDynamic(UTargetArrow* ArrowObj); //убирает стрелку-подсказку на экране(po etoi strelke-podskazke)

	UFUNCTION(Client, Reliable)
		void DeleteStrelkaBadOutline_Client(int32 ChelIndex);
	void RemoveArrowBadOutline(int32 ChelIndex); //убирает стрелку-подсказку на экране, которая указывает на плохо обведенного чела(который щас подох)

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
	/*UFUNCTION(Server, Reliable, WithValidation)
		void AddStoneDamageBuffTemp();*/

	void RemoveStoneDamageBuffTemp();

	UFUNCTION(Client, Reliable)
		void RefreshGeneratorArea();

	/*UFUNCTION(Client, Reliable)
		void StoneCountUpdate(int32 Count);*/

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
		void RAbility_HealPacket();

	void GoToWebCamServer(int32 Iterator);

	void GoToWebCam();

	UFUNCTION(Server, Reliable, WithValidation)
		void DeliverNicknameToServer(const FText& newNickName);
	//StoneThrowReplication
	/*UFUNCTION(Server, Reliable, WithValidation)
		void ThrowStoneServer(bool Type);*/

	UFUNCTION(Server, Reliable, WithValidation)
		void AddImmortalServer();
	void RemoveImmortalServer();

	/*UFUNCTION(NetMulticast, Reliable)
		void ThrowStoneMulticast(bool Type);*/

	UFUNCTION(Server, Reliable, WithValidation)
		void PickUp_Server();

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
		void ChangePB_Client(int32 ValueV);

	UFUNCTION(Server, Reliable, WithValidation)
		void AddInvisibleServer();

	UFUNCTION(BlueprintImplementableEvent)
		void InvisibleEverywhere();

	UFUNCTION(BlueprintImplementableEvent)
		void PlayRAbilitySound(class USoundWave* SoundWave);

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

	UFUNCTION(NetMulticast, Reliable) //легендарная связОчка
		void OutlineBad_Multicast();

	void RefreshOutline();

	void DeleteArrowDelayKeyShelter();
	void DeleteArrowDelayBoltorez();
	void DeleteArrowDelayOtvertka();

	void ReplaceQAbilityItem(UClass* QAbilityItemclass, int32 ItemIndex);

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

	/*UFUNCTION(NetMulticast, Reliable)
		void HideStoneMulticast();*/

	/*UFUNCTION(NetMulticast, Reliable)
		void ShowStoneMulticast();*/

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

	/*UFUNCTION()
		void OnTimelineFinished_Stone_First();*/
	/*UFUNCTION()
		void OnTimelineFinished_Stone_First_Left();*/

	/*UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
		*/
	/*UFUNCTION()
		void TimelineVectorReturn_Stone(FVector value);*/
	/*UFUNCTION()
		void TimelineVectorReturn_Stone_Left(FVector value);*/

	UFUNCTION()
		void TimelineFloatReturn_FOV_WebCam(float value);

	/*UFUNCTION()
		void OnTimelineFinished_Stone_Second();
	UFUNCTION()
		void OnTimelineFinished_Stone_Second_Left();*/

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

	UPROPERTY(EditAnywhere, Category = "UI HUD")
		TSubclassOf<UVerstakWidget> VerstakViewClass;

	void ChangePBPosition(int32 TypeChange);

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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UVerstakWidget* VerstakViewWidget;
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
	int32 AreaCode;
	UPROPERTY(Replicated)
		TArray<bool>DoesHave;
	TArray<int32>KeysCount;
	bool DoesHave_Owner;
	AInteractiveItem* LastInteractiveItem;
	AInteractiveItem* LastInteractiveItem_Server;
	ACoreItem* LastOutlineItem;
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
	//RAbility
	int8 ArmoryZelieCount;
	float ArmoryZelieEffect;

	int8 TempAntiDotCount;
	float TempAntiDotEffect;

	int8 ProjectileDamageCount;
	float ProjectileDamageEffect;
	//RAbility

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
	float RadCoeff = 1; //!!!!!!!!!!!!!! (для увеличения дамага в области газа)

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) //!!!!!!!!!!!!!!
	float MoveCoeff = 1; //!!!!!!!!!!!!!! (для уменьшения скорости в области льда)

	float CanalizationDamage;

	bool IsAwake;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) //!!!!!!!!!!!!!!
	TArray<AActor*>CustomizationChilds;

	TArray<UTargetArrow*> TargetArrowsStatic; //массив со стрелками-подсказками на экране
	TArray<AActor*> TargetItemsStatic; //массив с предметами, к которым привязаны стрелки-подсказки
	TArray<UTargetArrow*> TargetArrowsDynamic; //массив со стрелками-подсказками на экране
	TArray<AActor*> TargetItemsDynamic; //массив с предметами, к которым привязаны стрелки-подсказки

	TArray<UKDA_Stat*>MyKDA_Stat;
	UPROPERTY(BlueprintReadWrite)
	TArray<UConsumableAbility*>RAbilityPanel;
	UQAbility* CurQAbility;
	FTransform MeshTrans;
	FRotator BaseRotation;

	int32 LastRAbilityIndex;

	//ADezinfectorNasosZatichka* LastZatichka;
	AGeneratorArea* GenAreaObj;
	UGeneratorWidget* GeneratorView;

	ABP_PlayerController* MyController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNoteWidget* Widget_Note;

	AItemPromtArrow_MainExis* MainExis_Shelter;
	AItemPromtArrow_MainExis* MainExis_Ventilacia;
	AItemPromtArrow_MainExis* MainExis_Canalizacia;

	UPROPERTY(EditAnywhere)
		UObject* DefaultRAbilityImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bInEscMenu;
	bool TickEnableGeneratorWidget;
	bool bToRight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bInShopMenu;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsRentgenRender;

	bool DoubleArmThrowing;
	bool IsAlreadyCreated;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 AmountDetails;

	//--------------------------------------------------------------------------------------------------оружие---------------------------------
	UPROPERTY(EditAnywhere, Category = "Stone_Class")
		TSubclassOf<AWeapon_Character> Stone_Class;
	void FireEvent(); //нажатие на левую кнопку мыши
	UFUNCTION(Server, Reliable, WithValidation)
	void FireEvent_Server(); //выстреливаем из оружия на сервере

	void SwitchToFirstWeapon();
	void SwitchToSpecialWeapon();

	UFUNCTION(NetMulticast, Reliable)
		void CreateWeaponMulticast(UClass* WeaponCreatedClass, int32 Amount, int32 IdexSlot);
	UFUNCTION(Server, Reliable, WithValidation)
		void CreateWeaponServer(UClass* WeaponCreatedClass, int32 Amount, int32 IdexSlot);
	void CreateWeapon(UClass* WeaponCreatedClass, int32 Amount, int32 IndexSlot);

	void WeaponSwitch();
	UFUNCTION(Server, Reliable, WithValidation)
		void WeaponSwitch_Server(int32 SlotIndex);

	UFUNCTION(Server, Reliable, WithValidation)
		void DropSpecialGun_Server();

	void DropCoreItems(); //вываливает из себя имеющиеся ключевые предметы при смерти

	TArray<AWeapon_Character*> CurrentWeapons; //текущие оружия(камень + особое)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* WeaponPosition; //Позиция, на которую установится оружие
	int32 CurrentIndex; //индекс в массиве CurrentWeapons
	void SetWeaponToSlot(int32 IndexWeapon); //когда мы на клиенте и нужно поменять оружие в слоте клиента

	UFUNCTION(NetMulticast, Reliable)
		void SetWeaponToSlotMulticast(int32 IndexWeapon); //когда нужно с сервера установить у всех оружие в слот
	UFUNCTION(Server, Reliable, WithValidation)
	void SetWeaponToSlotServer(int32 IndexWeapon);
	
	UFUNCTION(NetMulticast, Reliable)
		void SwitchToFreeWeapon_Multicast();
	void SwitchToFreeWeapon(); //вызывается из Multicasat`а

	UFUNCTION(Client, Reliable)
	void ClearWeaponInfoClient(); //вызывается из выстрела оружия с сервера

	void ClearWeaponInfo();

	UFUNCTION(NetMulticast, Reliable)
		void HideCurrentWeapon();

	UFUNCTION(Server, Reliable, WithValidation)
	void ChangeAmmoServer(int32 NewLeftAmmmo, int32 indexWeapon);
	UFUNCTION(NetMulticast, Reliable)
	void ChangeAmmoClients(int32 NewLeftAmmmo, int32 indexWeapon); //меняет кол-во патронов у клиента-хозяина в оружии(игрока)

	UFUNCTION(Client, Reliable)
		void RefreshWidgetAmmoOwningClient(int32 NewLeftAmmo, int32 NewMaxAmmo, int32 NewCurIndex); //когда с сервера нужно поменять виджет у хозина hud
	void RefreshWidgetAmmoOwning(int32 NewLeftAmmo, int32 NewMaxAmmo, int32 NewCurIndex);

	UFUNCTION(NetMulticast, Reliable)
		void StartAnimInCurSlot();
	UFUNCTION(NetMulticast, Reliable)
		void StartAnimInCurSlotReverse(bool HaveAmmo);

	void InvertMovement(float timeToOff); // инвертированное управление при попадании бутылки, которое снимается через timeToOff

	bool CanFireWeapon; // может ли чел стрелять из оружия


	UFUNCTION(Server, Reliable, WithValidation)
		void GetAmmo_Server(); // для обновлениея патронов камня в начале игры

	UFUNCTION(NetMulticast, Reliable)
		void GetAmmo_Multicast(int32 Ammmmmmo); // для обновлениея патронов камня в начале игры
	//--------------------------------------------------------------------------------------------------оружиеEnd---------------------------------
};
