// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ConsumableAbility.h"
#include "ConsumableAbility_HealPacket.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT9_API UConsumableAbility_HealPacket : public UConsumableAbility
{
	GENERATED_BODY()

public:
	UConsumableAbility_HealPacket();
	void UseAbilityServer(AChel* Player) override;
	bool UseAbilityClient(AChel* Player) override;
};
