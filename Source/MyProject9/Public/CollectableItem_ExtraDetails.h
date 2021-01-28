// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CollectableItem.h"
#include "CollectableItem_ExtraDetails.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT9_API ACollectableItem_ExtraDetails : public ACollectableItem
{
	GENERATED_BODY()
public:
	ACollectableItem_ExtraDetails();

	void PickUpEventServer(AChel* Player) override;
	bool PickUpEventClient(AChel* Player) override;

	void ToggleCustomDepth(bool NewIsOutliningNow, AChel* Player) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* Mesh2;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* Mesh3;
	int32 Amount;
};
