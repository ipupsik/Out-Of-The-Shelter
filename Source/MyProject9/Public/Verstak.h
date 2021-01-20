// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveItem.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Verstak.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT9_API AVerstak : public AInteractiveItem
{
	GENERATED_BODY()
public:
	AVerstak();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Collision")
		UBoxComponent* Collision;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Scene")
		USceneComponent* Scene;
	void PickUpEventServer(AChel* Player) override;
	bool PickUpEventClient(AChel* Player) override;
	void OnLineTraced(AChel* Player) override;
	void ToggleCustomDepth(bool NewIsOutliningNow) override;
};
