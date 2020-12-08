// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

#include "Spectator.h"
#include "Cache.h"
#include "GeneratorArea.h"
#include "UI/GeneratorWidget.h"
#include "CanalizationButton.h"
#include "WebCamLocker.h"

#include "GI.h"
#include "GS.h"
#include "Stone.h"
#include "PickableItem.h"
#include "OpenAreaCPP.h"
#include "UI/UserView.h"
#include "UI/PlayerKillPlayer.h"
#include "UI/PlayerLostItem.h"
#include "UI/PlayerSuicide.h"
#include "UI/GeneratorWidget.h"
#include "Components/TimelineComponent.h"

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
	void OpenAreaPressed();
	void OpenAreaReleased();

	void UpdateSpectating_Left();
	void UpdateSpectating_Right();
public:
	void SpawnPlayer();
	void PossessedBy(AController* NewController) override;

	UFUNCTION(Client, Reliable)
		void StoneCountUpdate();

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
		void GoToWebCamServer(int32 Iterator);

	void GoToWebCam();

	UFUNCTION(Server, Reliable, WithValidation)
		void DeliverNicknameToServer(const FText& newNickName);
	//StoneThrowReplication
	UFUNCTION(Server, Reliable, WithValidation)
		void ThrowStoneServer(FTransform StoneTransform);

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
		void OutlineBad_Server();

	UFUNCTION(NetMulticast, Reliable) //легендарна€ св€зќчка
		void OutlineBad_Multicast();

	void RefreshOutline();

	UFUNCTION(Server, Reliable, WithValidation)
		void LockWebCam_Server();

	UFUNCTION(Client, Reliable)
		void HideWidgetStas();

	UFUNCTION(Client, Reliable)
		void AreaClosedUpdate(int32 EscapeWay);

	UFUNCTION(Client, Reliable)
		void RefreshWidgets_Winner(int32 EscapeWay);

	UFUNCTION(Client, Reliable)
		void UpdatePositionClient(FTransform NewTrans);

	UFUNCTION(Client, Reliable)
		void HideHudArea();

	UFUNCTION(Client, Reliable)
		void AddDoubleRadiationWidget();

	UFUNCTION(Client, Reliable)
		void DisableDoubleRadiationWidget();

	UFUNCTION(Client, Reliable)
		void ShowHudArea();

	UFUNCTION(NetMulticast, Reliable)
		void HideStoneMulticast();

	UFUNCTION(Client, Reliable)
		void RefreshWidgets(const TArray<bool> &whatToUpdate, int KillerNickIndex, int VictimNickIndex, bool isSuicide);
	//ThrowStoneFunctions
	FOnTimelineVector InterpFunction;
	FOnTimelineEvent TimelineFinishedFirst;
	FOnTimelineEvent TimelineFinishedSecond;
	UFUNCTION()
		void OnTimelineFinished_First();

	UFUNCTION()
		void TimelineFloatReturn(FVector value);

	UFUNCTION()
		void OnTimelineFinished_Second();

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
	
	//TimeLine
	UTimelineComponent* TimeLineFirst;
	UTimelineComponent* TimeLineSecond;

	UPROPERTY(EditAnywhere, Category = "Projectile")
		TSubclassOf<AStone> StoneClass;

	//HUD Class Variables
	UPROPERTY(EditAnywhere, Category = "UI HUD")
		TSubclassOf<UUserView> UserViewClass;
	UPROPERTY(EditAnywhere, Category = "UI HUD")
		TSubclassOf<UUserWidget> KillFeedClass;

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
	//HUD Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		UUserView* UserView;
	UUserWidget* KillFeed;
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
	ACanalizationButton* LastButton;
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

	//StoneAttackVars
	bool bIsAlreadyThrowing;
	UPROPERTY(EditAnywhere, Category = "Timeline")
		UCurveVector*  vCurve;

	FVector StonePosition;

	//KillFeed Vars
	int KillerIndex;

	int32 WebCamIterator;
	
public:
	//Logic Boolean Variables
	bool bLineTrace_is_need_refresh;
	bool bCanPossessWebCam;
	bool isTracedBad;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bCanWalkingAndWatching;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated)
		bool IsEnableInput;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) //!!!!!!!!!!!!!!
	bool IsSuccessOpening;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) //!!!!!!!!!!!!!!
	float RadCoeff = 1; //!!!!!!!!!!!!!! (дл€ увеличени€ дамага в области газа)

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) //!!!!!!!!!!!!!!
	float MoveCoeff = 1; //!!!!!!!!!!!!!! (дл€ уменьшени€ скорости в области льда)

	float CanalizationDamage;

	FTransform MeshTrans;

	AOpenAreaCPP* OpenAreaObj;

	AGeneratorArea* GenAreaObj;
	UGeneratorWidget* GeneratorView;

	APickableItem* LastOutlineItem;

	AWebCamLocker* LastWebCamLocker;
};
