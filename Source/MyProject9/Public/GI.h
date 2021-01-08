// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AdvancedFriendsGameInstance.h"
#include "Engine/GameInstance.h"
#include "UI/FinalMenu.h"

#include "GI.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT9_API UGI : public UAdvancedFriendsGameInstance
{
	GENERATED_BODY()

public:
	void Init() override;

	UPROPERTY(EditAnywhere, Category = "UI HUD")
		TSubclassOf<UFinalMenu> FinalMenuClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Sensetivity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText NickName;
};
