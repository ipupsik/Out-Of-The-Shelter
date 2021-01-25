// Fill out your copyright notice in the Description page of Project Settings.


#include "ConsumableAbility_Invisible.h"
#include "Chel.h"

void UConsumableAbility_Invisible::UseAbilityServer(AChel* Player)
{
	if (!Player->IsNowInvisible)
		Player->InvisibleEverywhere();
	else
	{
		Player->LastInvisibleAbilityObj->DestroyNonNativeProperties();
		Player->World->GetTimerManager().ClearTimer(Player->TimerHandleInvisible);
	}
	Player->LastInvisibleAbilityObj = this;
	Player->IsNowInvisible = true;
	TmpPlayer = Player;
	GetWorld()->GetTimerManager().SetTimer(Player->TimerHandleInvisible, this, &UConsumableAbility_Invisible::EndEffect, Duration, false);
}

void UConsumableAbility_Invisible::EndEffect()
{
	TmpPlayer->IsNowInvisible = false;
	TmpPlayer->ReverceInvisibleEverywhere();
	TmpPlayer->LastInvisibleAbilityObj = nullptr;
	DestroyNonNativeProperties();
}

bool UConsumableAbility_Invisible::UseAbilityClient(AChel* Player)
{
	UConsumableAbility::UseAbilityClient(Player);
	return true;
}