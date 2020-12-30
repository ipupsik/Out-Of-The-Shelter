// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/SizeBox.h"
#include "Components/Image.h"

#include "TargetArrow.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT9_API UTargetArrow : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
		USizeBox* SizeBoxMain;
	UPROPERTY(meta = (BindWidget))
		UImage* ArrowImg;
};
