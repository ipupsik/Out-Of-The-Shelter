// Fill out your copyright notice in the Description page of Project Settings.


#include "ConsumableAbility_ArmoryZelie.h"
#include "Chel.h"
#include "GS.h"
#include "InteractiveCache.h"

FVector UConsumableAbility_ArmoryZelie::GetCacheScale3D(int32 CacheIndex)
{
	AGS* GS = GetWorld()->GetGameState<AGS>();
	return GS->ZelieTransform[GS->Caches[CacheIndex]->CacheIndex].GetScale3D();
}

FRotator UConsumableAbility_ArmoryZelie::GetCacheRotation(int32 CacheIndex)
{
	AGS* GS = GetWorld()->GetGameState<AGS>();
	return FRotator(GS->ZelieTransform[GS->Caches[CacheIndex]->CacheIndex].GetRotation());
}

FVector UConsumableAbility_ArmoryZelie::GetCacheLocation(int32 CacheIndex)
{
	AGS* GS = GetWorld()->GetGameState<AGS>();
	return GS->ZelieTransform[GS->Caches[CacheIndex]->CacheIndex].GetLocation();
}

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
	UConsumableAbility::UseAbilityClient(Player);
	return true;
}