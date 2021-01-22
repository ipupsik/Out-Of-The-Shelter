// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Net/UnrealNetwork.h"
#include "InteractiveItem.h"
#include "Components/BoxComponent.h"

#include "OpenArea.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT9_API AOpenArea : public AInteractiveItem
{
	GENERATED_BODY()

public:
	AOpenArea();

	virtual void DoSomethink();

	//void GetLifetimeReplicatedProps(TArray < FLifetimeProperty >& OutLifetimeProps) const override;

	UFUNCTION(BlueprintImplementableEvent)
		void RotateVentilServer();
	UFUNCTION(BlueprintImplementableEvent)
		void RotateVentilServerReverse();
	

	int32 areaType;
	UPROPERTY(Replicated)
		bool bIsAvaliable;
	UPROPERTY(Replicated, BlueprintReadWrite)
		bool bIsUsed;
	UPROPERTY(Replicated, BlueprintReadWrite)
		float CurTimeVentil;
	
};
