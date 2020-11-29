// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

#include "PlayerLostItem.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT9_API UPlayerLostItem : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* Player;

	UPROPERTY(meta = (BindWidget))
		UImage* IMG_Boltorez;

	UPROPERTY(meta = (BindWidget))
		UImage* IMG_Otvertka;

	UPROPERTY(meta = (BindWidget))
		UImage* IMG_KeyShelter;
};
