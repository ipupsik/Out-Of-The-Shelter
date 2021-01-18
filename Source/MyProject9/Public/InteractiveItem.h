// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Chel.h"
#include "InteractiveItem.generated.h"


UCLASS()
class MYPROJECT9_API AInteractiveItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AInteractiveItem();

	UPROPERTY(EditAnywhere)
	bool bCanInterract;
	UPROPERTY(EditAnywhere)
	int32 colorOutlineType;
	UPROPERTY(EditAnywhere)
	bool IsOutliningNow;
	virtual void ToggleCustomDepth(bool NewIsOutliningNow);
	virtual void SetOutlineColor(int32 ColorOutline);

	virtual void PickUpEventServer(AChel* Player );
	virtual void PickUpEventClient(AChel* Player);

};
