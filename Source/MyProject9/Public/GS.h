// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Net/UnrealNetwork.h"
#include "CodeNote_New.h"
#include "TerminalNumber.h"
#include "BP_PlayerController.h"
#include "TerminalLight.h"
#include "CodeNote_New.h"
#include "FinalMenuPawn.h"
#include "Cache.h"
#include "WebCamPoint.h"
#include "ItemPromtArrow.h"
#include "Weapon_Level.h"

//для рандомного события - start
#include "DamageAreaRandomEvent.h"
#include "ParticleGasRandomEvent.h"
//для рандомного события - end

#include "GS.generated.h"

class ASpectator;
class ACollectableItem;

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
class AInteractiveCache;

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
		


	UPROPERTY(EditAnywhere, Category = "RandomEvent")
		TSubclassOf<ADamageAreaRandomEvent> DamageAreaRandom_Class;
	UPROPERTY(EditAnywhere, Category = "RandomEvent")
		TSubclassOf<AParticleGasRandomEvent> ParticleGas_Class;
	UPROPERTY(EditAnywhere, Category = "RandomEvent")
		float RandomEventDuration;
	UPROPERTY(EditAnywhere, Category = "RandomEvent")
		FName GasAreaDamageTag;
	UPROPERTY(EditAnywhere, Category = "RandomEvent")
		FName GasAreaParticleTag;

	void CreateGasOnFloor();
	void RemoveGasFromFloor();

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
		TSubclassOf<AInteractiveItem> HealPacket_class;
	UPROPERTY(EditAnywhere, Category = "ItemClasses")
		TSubclassOf<AInteractiveItem> InvisiblePotion_class;
	UPROPERTY(EditAnywhere, Category = "ItemClasses")
		TSubclassOf<AInteractiveItem> AntiRadZelie_class;
	UPROPERTY(EditAnywhere, Category = "ItemClasses")
		TSubclassOf<AInteractiveItem> ArmoryZelie_class;
	UPROPERTY(EditAnywhere, Category = "ItemClasses")
		TSubclassOf<AInteractiveItem> ProjectileZelie_class;

	UPROPERTY(EditAnywhere, Category = "ItemClasses")
		TSubclassOf<AActor> InvisiblePotion;

	UPROPERTY(EditAnywhere, Category = "ItemClasses")
		TSubclassOf<AInteractiveItem> BronzeKey;
	UPROPERTY(EditAnywhere, Category = "ItemClasses")
		TSubclassOf<AInteractiveItem> SilverKey;
	UPROPERTY(EditAnywhere, Category = "ItemClasses")
		TSubclassOf<AInteractiveItem> GoldKey;

	UPROPERTY(EditAnywhere, Category = "ItemClasses")
		TSubclassOf<AWeapon_Level> Axe_Class;
	UPROPERTY(EditAnywhere, Category = "ItemClasses")
		TSubclassOf<AWeapon_Level> Bottle_Class;
	UPROPERTY(EditAnywhere, Category = "ItemClasses")
		TSubclassOf<AWeapon_Level> Knife_Class;

	UPROPERTY(EditAnywhere, Category = "ItemClasses")
		TSubclassOf<AInteractiveItem> AmmoBackPack_Class;

	UPROPERTY(EditAnywhere, Category = "ItemClasses")
		TSubclassOf<AInteractiveItem> Details_class;

	UPROPERTY(EditAnywhere, Category = "ItemClasses")
		TSubclassOf<AInteractiveItem> CodeNoteClass;
	UPROPERTY(EditAnywhere, Category = "ItemClasses")
		TSubclassOf<ATerminalNumber> NumberTerminalClass;

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
	UPROPERTY(Replicated)
	bool IsCanalizaciaPlayed;

	TArray<FTransform>Keys_Transform;
	TArray<bool>Keys_IsAvaliable;
	TArray<FTransform>Details_Transform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<bool>Details_IsAvaliable;

	TArray<AInteractiveCache*>Caches;
	TArray<bool>CacheItems_Stuff_IsAvaliable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FTransform TransformOfFirstNum;
	int32 CurrentCode;
	ATerminalLight* LampObj;
	UPROPERTY(Replicated)
		TArray<ATerminalNumber*> NumbersOnPanel;
	UPROPERTY(EditAnywhere)
		FName CodeNoteTargetTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FTransform> KeyShelterTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FTransform> HealPacketTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FTransform> ZelieTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FTransform> ArmoryZelieTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FTransform> AxeTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FTransform> BottleTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FTransform> KnifeTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FTransform> BoltorezTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FTransform> OtvertkaTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FTransform> AmmoBackPackTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FTransform> ChelDetectorTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FTransform> RentgenGlassTransform;

	int32 MaxPlayersCount;
};
