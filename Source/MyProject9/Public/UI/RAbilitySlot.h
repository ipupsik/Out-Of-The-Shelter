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
	UFUNCTION()
		void SelectRAbility();

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		UTextBlock* CountText;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		UImage* AbilityImage;

	void NativeConstruct() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 InArrayIndex;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* BTN_Select;
};
