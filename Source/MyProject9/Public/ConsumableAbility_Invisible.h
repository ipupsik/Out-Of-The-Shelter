// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ConsumableAbility.h"
#include "ConsumableAbility_Invisible.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT9_API UConsumableAbility_Invisible : public UConsumableAbility
{
	GENERATED_BODY()
public:
	bool UseAbilityClient(AChel* Player) override;
	void UseAbilityServer(AChel* Player) override;

	void EndEffect();

	int32 CurAbilityUsing;

	AChel* TmpPlayer;
};
