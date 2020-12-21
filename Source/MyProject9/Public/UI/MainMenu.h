// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Components/TextBlock.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT9_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION() void OnClick();

	UPROPERTY(meta = (BindWidget))
		UButton* PasteButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UEditableText* ServerConnectID;

	void NativeConstruct() override;
	
};
