// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickableItem.h"
#include "Net/UnrealNetwork.h"
#include "Components/BoxComponent.h"

#include "OpenArea.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT9_API AOpenArea : public APickableItem
{
	GENERATED_BODY()

public:
	AOpenArea();

	virtual void DoSomethink();

	void GetLifetimeReplicatedProps(TArray < FLifetimeProperty >& OutLifetimeProps) const override;

	

	UPROPERTY(EditAnywhere)
		int32 areaType;
	UPROPERTY(Replicated)
		bool bIsAvaliable;
	
};
