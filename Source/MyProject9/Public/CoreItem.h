// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CollectableItem.h"
#include "CoreItem.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT9_API ACoreItem : public ACollectableItem
{
	GENERATED_BODY()
public:
	ACoreItem();

	void PickUpEventServer(AChel* Player) override;
	void PickUpEventClient(AChel* Player) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TypeItem;
};
