// Fill out your copyright notice in the Description page of Project Settings.


#include "ConsumableAbility_ArmoryZelie.h"
#include "Chel.h"

void UConsumableAbility_ArmoryZelie::UseAbilityServer(AChel* Player)
{
	Player->ArmoryZelieCount++;
	Player->ArmoryZelieEffect = 0;
	TmpPlayer = Player;
	FTimerHandle FuzeTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(FuzeTimerHandle, this, &UConsumableAbility_ArmoryZelie::EndEffect, Duration, false);
}

void UConsumableAbility_ArmoryZelie::EndEffect()
{
	TmpPlayer->ArmoryZelieCount--;
	if (TmpPlayer->ArmoryZelieCount == 0)
	{
		TmpPlayer->ArmoryZelieEffect = 1.0f;
	}
	DestroyNonNativeProperties();
}

bool UConsumableAbility_ArmoryZelie::UseAbilityClient(AChel* Player)
{
	return true;
}