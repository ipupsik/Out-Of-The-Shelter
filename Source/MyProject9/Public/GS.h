// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Net/UnrealNetwork.h"
#include "PickableItem.h"
#include "BP_PlayerController.h"
#include "TerminalLight.h"
#include "NumberTerminal.h"
#include "Code_Note.h"
#include "FinalMenuPawn.h"
#include "Cache.h"
#include "WebCamPoint.h"
#include "ItemPromtArrow.h"
#include "GS.generated.h"

class ASpectator;

#define MIN_COUNT_KeyShelter 4
#define MIN_COUNT_Boltorez 4
#define MIN_COUNT_Otvertka 4
#define MIN_COUNT_Rentgen 4
#define MIN_COUNT_ChelDetector 4

#define MAX_COUNT_KeySHelter 5
#define MAX_COUNT_Boltorez 5
#define MAX_COUNT_Otvertka 5
#define MAX_COUNT_Rentgen 5
#define MAX_COUNT_ChelDetector 5

#define STONE_DAMAGE 0.15f
#define DeltaRadiation 0.1f

#define SPAWN_TIME 20.f
#define ShowRandomItem_TIME 6
#define ShowMainExis_TIME 8

#define COUNT_CacheKey 7
/**
 * 
 */

class AAreaCollision;
class AInteractiveItem;

UCLASS()
class MYPROJECT9_API AGS : public AGameStateBase
{
	GENERATED_BODY()

public:
	AGS();
	void GetLifetimeReplicatedProps(TArray < FLifetimeProperty >& OutLifetimeProps) const override;
	
	void GameBegin();

	void Tick(float DeltaSeconds) override;
	void BeginPlay() override;

	void EventSpawnNote();
	void RefreshGenerator();
	void AddNumToTerminal(int32 Number);
	void DeleteLastNumber();
	void CheckCode(int Index);

	void ChangeLamp_Neutral();

	UFUNCTION(BlueprintImplementableEvent)
		void SpawnCustomizationChels();

	UFUNCTION(BlueprintImplementableEvent)
		void PlayGoodSoundTerminal(FVector Location);

	UFUNCTION(BlueprintImplementableEvent)
		void PlayBadSoundTerminal(FVector Location);

	UFUNCTION(BlueprintImplementableEvent)
		void ClickOnButtonTerminal(FVector Location);

	UFUNCTION()
		void SpawnPlayers();
	UFUNCTION(BlueprintCallable)
		void ResetGame();

public:
	//For indexing
	UPROPERTY(BlueprintReadWrite)
		int AmountOfPlayers;
	int AcceptPiedistalAmount;
	//Rematch
	UPROPERTY(BlueprintReadWrite)
		int AgreedPlayers;

	UPROPERTY(BlueprintReadWrite)
		TArray<FText> WinnersNickNames;
	UPROPERTY(BlueprintReadWrite)
		TArray<int32> WinnersIndex;
	UPROPERTY(BlueprintReadWrite)
		TArray<int32> EscapeTime;
	TArray<FText> NickNames;
	//UPROPERTY(Replicated)
		//TArray<FText> Kills;
	//UPROPERTY(Replicated)
		//TArray<FText> Deaths;
	
	TArray<ASpectator*> Spectators;
	UPROPERTY(Replicated)
		TArray<bool> AreaAvaliables;
	UPROPERTY(Replicated)
		TArray<bool> AreaClosed;
	TArray<AAreaCollision*>Areas;
	TArray<AWebCamPoint*>WebCams;
	UPROPERTY(Replicated)
		int32 CodeGenerator;
	UPROPERTY(Replicated)
		bool IsCodeTerminalAvaliable;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
		bool ButtonPlayAnim;

	UPROPERTY(EditAnywhere, Category = "FinalMenuP")
		TSubclassOf<AFinalMenuPawn> FMP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FTransform TransFMP;
		

	UPROPERTY(EditAnywhere, Category = "ItemClasses")
		TSubclassOf<AInteractiveItem> KeyShelter;
	UPROPERTY(EditAnywhere, Category = "ItemClasses")
		TSubclassOf<AInteractiveItem> Boltorez;
	UPROPERTY(EditAnywhere, Category = "ItemClasses")
		TSubclassOf<AInteractiveItem> Otvertka;
	UPROPERTY(EditAnywhere, Category = "ItemClasses")
		TSubclassOf<AInteractiveItem> ChelDetector_class;
	UPROPERTY(EditAnywhere, Category = "ItemClasses")
		TSubclassOf<AInteractiveItem> RentgenGlass_class;

	UPROPERTY(EditAnywhere, Category = "ItemClasses")
		TSubclassOf<AActor> InvisiblePotion;

	UPROPERTY(EditAnywhere, Category = "ItemClasses")
		TSubclassOf<AInteractiveItem> BronzeKey;
	UPROPERTY(EditAnywhere, Category = "ItemClasses")
		TSubclassOf<AInteractiveItem> SilverKey;
	UPROPERTY(EditAnywhere, Category = "ItemClasses")
		TSubclassOf<AInteractiveItem> GoldKey;

	UPROPERTY(EditAnywhere, Category = "ItemClasses")
		TSubclassOf<AInteractiveItem> CodeNoteClass;
	UPROPERTY(EditAnywhere, Category = "ItemClasses")
		TSubclassOf<ANumberTerminal> NumberTerminalClass;

	int CurrentOtvertka;
	int CurrentKeyShelter;
	int CurrentBoltorez;
	int32 VentilaciaRubilnickCount;
	int32 CanalizaciaNasosCount;

	int CurrentButtonCount;

	int CurrentTime;

	int32 GeneralLayer;
	UPROPERTY(Replicated)
		bool IsShelterAvaliable;
	UPROPERTY(Replicated)
		bool IsVentilaciaAvaliable;
	UPROPERTY(Replicated)
		bool IsCanalizaciaAvaliable;
	bool IsGameStarted;

	TArray<FTransform>Keys_Transform;
	TArray<bool>Keys_IsAvaliable;

	TArray<ACache*>Caches;
	TArray<bool>CacheItems_Stuff_IsAvaliable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FTransform TransformOfFirstNum;
	int32 CurrentCode;
	ATerminalLight* LampObj;
	UPROPERTY(Replicated)
		TArray<ANumberTerminal*> NumbersOnPanel;
	UPROPERTY(EditAnywhere)
		FName CodeNoteTargetTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FTransform> KeyShelterTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FTransform> BoltorezTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FTransform> OtvertkaTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FTransform> ChelDetectorTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FTransform> RentgenGlassTransform;

	int32 MaxPlayersCount;
};
