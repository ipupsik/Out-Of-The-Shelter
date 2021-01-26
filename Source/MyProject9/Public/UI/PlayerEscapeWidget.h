// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "PlayerEscapeWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT9_API UPlayerEscapeWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
		UTextBlock* NickName;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* WayOut;

	UPROPERTY(meta = (BindWidget))
		UImage* OtvertkaImage;
	UPROPERTY(meta = (BindWidget))
		UImage* BoltorezImage;
	UPROPERTY(meta = (BindWidget))
		UImage* KeyShelterImage;
};
