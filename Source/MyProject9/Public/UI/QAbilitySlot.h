// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "QAbilitySlot.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT9_API UQAbilitySlot : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		UImage* AbilityImage;
};
