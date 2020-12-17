// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
#include "KillFeed.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT9_API UKillFeed : public UUserWidget
{
	GENERATED_BODY()
public:
	//---------------------------
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UVerticalBox* VB_KillFeed;
};
