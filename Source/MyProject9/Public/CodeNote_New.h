// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveItem.h"
#include "CodeNote_New.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT9_API ACodeNote_New : public AInteractiveItem
{
	GENERATED_BODY()
public:
	ACodeNote_New();
	
	UFUNCTION(BlueprintImplementableEvent)
		void PlayPickUpSound();

	bool PickUpEventClient(AChel* Player) override;
	void OnLineTraced(AChel* Player) override;
	void ToggleCustomDepth(bool NewIsOutliningNow, AChel* Player) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Collision")
		UBoxComponent* Collision;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Scene")
		USceneComponent* Scene;
};
