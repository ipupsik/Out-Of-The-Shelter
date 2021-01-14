// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "KDA_Stat.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT9_API UKDA_Stat : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* NickName;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* Deaths;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* Kills;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* Ping;

	int32 PlayerIndex;
	int32 KillsCount;
	int32 DeathsCount;
};
