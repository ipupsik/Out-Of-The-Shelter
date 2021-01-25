// Fill out your copyright notice in the Description page of Project Settings.


#include "ConsumableAbility_TempAntiDot.h"
#include "Chel.h"

void UConsumableAbility_TempAntiDot::UseAbilityServer(AChel* Player)
{
	Player->TempAntiDotCount++;
	Player->TempAntiDotEffect = 0;
	TmpPlayer = Player;
	FTimerHandle FuzeTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(FuzeTimerHandle, this, &UConsumableAbility_TempAntiDot::EndEffect, Duration, false);
}

void UConsumableAbility_TempAntiDot::EndEffect()
{
	TmpPlayer->TempAntiDotCount--;
	if (TmpPlayer->TempAntiDotCount == 0)
	{
		TmpPlayer->TempAntiDotEffect = 1.0f;
	}
	DestroyNonNativeProperties();
}

bool UConsumableAbility_TempAntiDot::UseAbilityClient(AChel* Player)
{
	return true;
}
