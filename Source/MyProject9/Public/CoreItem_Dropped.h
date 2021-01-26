// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CollectableItem.h"
#include "CoreItem_Dropped.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT9_API ACoreItem_Dropped : public ACollectableItem
{
	GENERATED_BODY()
public:
	ACoreItem_Dropped();

	void PickUpEventServer(AChel* Player) override;
	bool PickUpEventClient(AChel* Player) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 TypeItem;
	
};
