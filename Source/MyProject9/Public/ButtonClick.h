// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveItem.h"
#include "Components/DecalComponent.h"
#include "ButtonClick.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT9_API AButtonClick : public AInteractiveItem
{
	GENERATED_BODY()
	
public:
	AButtonClick();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void ButtonPressAnimation();

	UPROPERTY(EditAnywhere)
		int32 ButtonType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Decal")
		UDecalComponent* Decal;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Collision")
		UBoxComponent* Collision;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Scene")
		USceneComponent* Scene;

public:
	virtual void ToggleCustomDepth(bool NewIsOutliningNow, AChel* Player);

	virtual void PickUpEventServer(AChel* Player);
	virtual bool PickUpEventClient(AChel* Player);
	virtual void OnLineTraced(AChel* Player);
};
