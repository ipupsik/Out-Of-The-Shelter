// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveItem.h"
#include "CoreAreas.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT9_API ACoreAreas : public AInteractiveItem
{
	GENERATED_BODY()
public:
	ACoreAreas();
	void SetOutlineColor(int32 ColorOutline) override;
	void OnLineTraced(AChel* Player) override;
	void PickUpEventServer(AChel* Player) override;
	bool PickUpEventClient(AChel* Player);
	bool PickUpEventReleaseClient(AChel* Player) override;
	void PickUpEventReleaseServer(AChel* Player) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Collision")
		UBoxComponent* Collision;


};
