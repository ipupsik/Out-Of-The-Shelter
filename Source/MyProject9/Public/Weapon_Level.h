// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CollectableItem.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Weapon_Level.generated.h"
/**
 * 
 */
class AWeapon_Character;
UCLASS()
class MYPROJECT9_API AWeapon_Level : public ACollectableItem
{
	GENERATED_BODY()
public:
	AWeapon_Level();

	void PickUpEventServer(AChel* Player) override;
	void PickUpEventClient(AChel* Player) override;


	UFUNCTION(NetMulticast, Reliable)
	void ChangeAmount(int32 NewAmount);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon_Class")
		TSubclassOf<AWeapon_Character> WeaponClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Amount;
};
