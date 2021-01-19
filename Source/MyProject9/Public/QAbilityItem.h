// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CollectableItem.h"
#include "QAbilityItem.generated.h"

class UQAbility;
/**
 * 
 */
UCLASS()
class MYPROJECT9_API AQAbilityItem : public ACollectableItem
{
	GENERATED_BODY()
public:
	AQAbilityItem();

	virtual void PickUpEventServer(AChel* Player) override;
	virtual void PickUpEventClient(AChel* Player) override;

	UPROPERTY(EditAnywhere, Category = "Main_Vars")
		TSubclassOf<UQAbility> QAbility_class;
};
