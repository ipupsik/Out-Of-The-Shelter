// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/Slider.h"


#include "GeneratorWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT9_API UGeneratorWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeConstruct() override;
	
	UPROPERTY(meta = (BindWidget))
		USlider* Corretca;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* RepairText;

	UPROPERTY(meta = (BindWidget))
		UProgressBar* PB_Repair;

	bool bToRight;
	UPROPERTY(EditAnywhere)
	float curSpeed;
	UPROPERTY(EditAnywhere)
	float delta;
	UPROPERTY(EditAnywhere)
	TArray<float> PositionX;
	UPROPERTY(EditAnywhere)
	TArray<float> Speed;
	bool TickEnable;
	
	
};
