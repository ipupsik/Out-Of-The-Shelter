// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "RAbilitySlot.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT9_API URAbilitySlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	int32 AbilityType;
	int32 Count;
	int32 InArrayIndex;
	
	UFUNCTION()
		void SelectRAbility();

	UPROPERTY(meta = (BindWidget))
		UTextBlock* CountText;
	UPROPERTY(meta = (BindWidget))
		UImage* AbilityImage;

	void NativeConstruct() override;


	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* BTN_Select;
};
