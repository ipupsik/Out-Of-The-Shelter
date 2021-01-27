// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "IconWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT9_API UIconWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	int32 Identificator;
	UImage* IconEffect;
	
};
