// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/KismetMathLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"

#include "Spectator.h"
#include "FinalMenuPawn.h"
#include "Cache.h"
#include "GeneratorArea.h"
#include "UI/GeneratorWidget.h"
#include "ButtonCanalization.h"
#include "WebCamLocker.h"
#include "ClickButton.h"
#include "UI/KillFeed.h"
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
	
	// Actions functions
	void MyJump();
	void StartSprint();
	void StopSprint();
	void ShowKillFeed();
	void UnShowKillFeed();

	void ThrowStone();
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
	void SpawnPlayer();
	void PossessedBy(AController* NewController) override;


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


	void GoToWebCamServer(int32 Iterator);

	void GoToWebCam();

	UFUNCTION(Server, Reliable, WithValidation)
		void DeliverNicknameToServer(const FText& newNickName);
	//StoneThrowReplication
	UFUNCTION(Server, Reliable, WithValidation)
		void ThrowStoneServer();


	UFUNCTION(NetMulticast, Reliable)
		void ThrowStoneMulticast();

	UFUNCTION(Server, Reliable, WithValidation)
		void NewHaveItemServer(int32 ItemType);

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

	void DoTraceOpenArea();

	UFUNCTION(NetMulticast, Reliable) //легендарна€ св€зќчка
		void OutlineBad_Multicast();

	void RefreshOutline();

	void DeleteArrowDelay();

	UFUNCTION(Server, Reliable, WithValidation)
		void LockWebCam_Server();

	UFUNCTION(Client, Reliable)
		void HideNoteWidget();

	UFUNCTION(Client, Reliable)
		void HideWidgetStas();

	UFUNCTION(Client, Reliable)
		void AreaClosedUpdate(int32 EscapeWay);

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
		void AddChromaticAbberationClient();

	UFUNCTION(Client, Reliable)
		void SetCameraRotationWebCam(float RollRot, float PitchRot, float YawRot);

	UFUNCTION(Client, Reliable)
		void RefreshWidgets(const TArray<bool> &whatToUpdate, int KillerNickIndex, int VictimNickIndex);
	UFUNCTION()
		void OnTimelineFinished_Stone_First();

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void TimelineVectorReturn_Stone(FVector value);
	UFUNCTION()
		void TimelineFloatReturn_FOV_WebCam(float value);

	UFUNCTION()
		void OnTimelineFinished_Stone_Second();

	UFUNCTION()
		void SleepAnimation_End();

	UFUNCTION()
		void AwakeAnimation_End();

	void StoneAttack(int StoneIndex);
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
		UStaticMeshComponent* Stone;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
		UCapsuleComponent* DamageCollision;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
		USceneComponent* Scene;

	UPROPERTY(EditAnywhere, Category = "Projectile")
		TSubclassOf<AStone> StoneClass;

	//HUD Class Variables
	UPROPERTY(EditAnywhere, Category = "UI HUD")
		TSubclassOf<UUserView> UserViewClass;

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
		TSubclassOf<UKillFeed> KillFeed_class;
	UPROPERTY(EditAnywhere, Category = "UI HUD") //класс стрелки подсказки
		TSubclassOf<UTargetArrow> TargetArrowClass;

	//HUD Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		UUserView* UserView;
	UKillFeed* KillFeed;
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
	UPROPERTY(EditAnywhere, Replicated, Category = "PlayerVariables")
		int Kills;
	UPROPERTY(EditAnywhere, Replicated, Category = "PlayerVariables")
		int Death;
	//InGameVariables
	UPROPERTY(EditAnywhere, Replicated, Category = "InGameVariables")
		bool IsInGame;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vars")
	int32 ItemCodePickUp;
	int32 AreaCode;
	UPROPERTY(Replicated)
		TArray<bool>DoesHave;
	UPROPERTY(Replicated)
		TArray<int32>KeysCount;
	bool DoesHave_Owner;
	APickableItem* LastItem;
	ACache* LastCache;
	AButtonCanalization* LastButton;
	//GlobalSettings
	bool IsServerAuth;
	bool IsPlayerOwner;
	UWorld* World;
	//Settings Variables
	UPROPERTY(EditAnywhere, Category = "Settings")
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

	UTimelineComponent* TimeLine_FOV_WebCam;
	//ThrowStoneFunctions
	FOnTimelineVector InterpFunction_Stone;
	FOnTimelineEvent TimelineFinished_Stone_First;
	FOnTimelineEvent TimelineFinished_Stone_Second;

	FOnTimelineFloat InterpFunction_FOV_WebCam;


	//StoneAttackVars
	bool bIsAlreadyThrowing;
	UPROPERTY(EditAnywhere, Category = "Timeline")
		UCurveVector*  vCurveStone;
	UPROPERTY(EditAnywhere, Category = "Timeline")
		UCurveFloat* vCurveFOV_WebCam;
	FVector StonePosition;

	//KillFeed Vars
	int KillerIndex;

	int32 WebCamIterator;
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

	FTransform MeshTrans;
	FRotator BaseRotation;

	AGeneratorArea* GenAreaObj;
	UGeneratorWidget* GeneratorView;

	APickableItem* LastOutlineItem;

	AWebCamLocker* LastWebCamLocker;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNoteWidget* Widget_Note;

	UTargetArrow* ArrowShelter;
	UTargetArrow* ArrowCanalizacia;
	UTargetArrow* ArrowVentilacia;

	AItemPromtArrow_MainExis* MainExis_Shelter;
	AItemPromtArrow_MainExis* MainExis_Ventilacia;
	AItemPromtArrow_MainExis* MainExis_Canalizacia;

	int32 ExisType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bInEscMenu;
};
