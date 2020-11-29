// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"

#include "PlayerKillPlayer.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT9_API UPlayerKillPlayer : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* Killer;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* Victim;
};
