// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CollectableItem.h"
#include "CacheKey.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT9_API ACacheKey : public ACollectableItem
{
	GENERATED_BODY()
public:
	ACacheKey();

	void PickUpEventServer(AChel* Player) override;
	bool PickUpEventClient(AChel* Player) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TypeKey;

	void RemoveAndRefreshTimer();

	void Refresh();

	UFUNCTION(NetMulticast, Reliable)
		void ReplaceMulticast(FTransform NewTrans);

	UFUNCTION(NetMulticast, Reliable)
		void RefreshMulticast();
};
