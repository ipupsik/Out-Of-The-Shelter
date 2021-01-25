// Fill out your copyright notice in the Description page of Project Settings.


#include "ConAbility_ProjectileDamage.h"
#include "Chel.h"

void UConAbility_ProjectileDamage::UseAbilityServer(AChel* Player)
{
	Player->ProjectileDamageCount++;
	Player->ProjectileDamageEffect = 2.0;
	TmpPlayer = Player;
	FTimerHandle FuzeTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(FuzeTimerHandle, this, &UConAbility_ProjectileDamage::EndEffect, Duration, false);
}

void UConAbility_ProjectileDamage::EndEffect()
{
	TmpPlayer->ProjectileDamageCount--;
	if (TmpPlayer->ProjectileDamageCount == 0)
	{
		TmpPlayer->ProjectileDamageEffect = 1.0f;
	}
	DestroyNonNativeProperties();
}

bool UConAbility_ProjectileDamage::UseAbilityClient(AChel* Player)
{
	UConsumableAbility::UseAbilityClient(Player);
	return true;
}
