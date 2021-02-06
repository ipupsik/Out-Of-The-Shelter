// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "PlayerActivateGasOnFloor.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT9_API UPlayerActivateGasOnFloor : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(meta = (BindWidget))
		UTextBlock* Floor;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* NickName;
};
