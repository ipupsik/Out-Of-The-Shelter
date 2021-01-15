// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/WidgetSwitcher.h"
#include "Components/VerticalBox.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "Inventory.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT9_API UInventory : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
		UUniformGridPanel* RAbilityPanel;
	
	//UPROPERTY(meta = (BindWidget))
		//UUniformGridPanel* WeaponsPanel;

	//UPROPERTY(meta = (BindWidget))
		//UImage* QAbility;
};
