// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveItem.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "CollectableItem.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT9_API ACollectableItem : public AInteractiveItem
{
	GENERATED_BODY()
public:
	ACollectableItem();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayPickUpSound();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Collision")
		UBoxComponent* Collision;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Scene")
		USceneComponent* Scene;
	void ToggleCustomDepth(bool IsOutliningNow, AChel* Player) override;
	void SetOutlineColor(int32 ColorOutline) override;
	virtual void OnLineTraced(AChel* Player) override;

	int32 EnabledArrayIndex;
};
