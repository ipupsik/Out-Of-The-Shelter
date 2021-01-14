// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
#include "Tab.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT9_API UTab : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
		UVerticalBox* Tab_KD_Stat;
};
