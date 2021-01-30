// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GM.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT9_API AGM : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
		void Respawn();

};
