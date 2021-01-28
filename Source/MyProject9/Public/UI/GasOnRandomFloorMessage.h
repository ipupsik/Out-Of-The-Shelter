// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "GasOnRandomFloorMessage.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT9_API UGasOnRandomFloorMessage : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
		UTextBlock* Floor;
};
