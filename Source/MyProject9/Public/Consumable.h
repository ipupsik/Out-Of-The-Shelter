// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CollectableItem.h"
#include "Consumable.generated.h"

class UConsumableAbility;
/**
 * 
 */
UCLASS()
class MYPROJECT9_API AConsumable : public ACollectableItem
{
	GENERATED_BODY()
public:
	AConsumable();

	virtual void PickUpEventServer(AChel* Player) override;
	virtual void PickUpEventClient(AChel* Player) override;

	UPROPERTY(EditAnywhere, Category = "Main_Vars")
		TSubclassOf<UConsumableAbility> Ability_class;
};
