// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveItem.h"
#include "BP_VentilaciaRubilnick.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT9_API ABP_VentilaciaRubilnick : public AInteractiveItem
{
	GENERATED_BODY()
	
public:
	ABP_VentilaciaRubilnick();

	UFUNCTION(BlueprintImplementableEvent)
		void Open();

	void CheckVentilaciaAvaliable();

	UFUNCTION(NetMulticast, Reliable)
		void ChangeAvaliable();

	void PickUpEventServer(AChel* Player) override;
	bool PickUpEventClient(AChel* Player) override;
	void ToggleCustomDepth(bool NewIsOutliningNow, AChel* Player) override;

	void OnLineTraced(AChel* Player) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
		UStaticMeshComponent* Item;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
		UBoxComponent* Collision;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
		USceneComponent* Scene;
};
