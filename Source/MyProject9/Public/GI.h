// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UI/FinalMenu.h"

#include "GI.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT9_API UGI : public UGameInstance
{
	GENERATED_BODY()

public:
	void Init() override;

	UPROPERTY(EditAnywhere, Category = "UI HUD")
		TSubclassOf<UFinalMenu> FinalMenuClass;
	float Sensetivity;
	FText NickName;
};
