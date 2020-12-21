// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "EscapeMenu.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT9_API UEscapeMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION() void OnClick();

	UPROPERTY(meta = (BindWidget)) 
		UButton* DoneButton;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* NetID;

	void NativeConstruct() override;
};
