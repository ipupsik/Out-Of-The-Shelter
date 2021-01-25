// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CollectableItem.h"
#include "Details.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT9_API ADetails : public ACollectableItem
{
	GENERATED_BODY()
public:
	ADetails();

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
