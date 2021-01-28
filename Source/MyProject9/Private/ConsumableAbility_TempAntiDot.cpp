// Fill out your copyright notice in the Description page of Project Settings.


#include "ConsumableAbility_TempAntiDot.h"
#include "Chel.h"
#include "GS.h"
#include "InteractiveCache.h"

FVector UConsumableAbility_TempAntiDot::GetCacheScale3D(int32 CacheIndex)
{
	AGS* GS = GetWorld()->GetGameState<AGS>();
	return GS->ZelieTransform[GS->Caches[CacheIndex]->CacheIndex].GetScale3D();
}

FRotator UConsumableAbility_TempAntiDot::GetCacheRotation(int32 CacheIndex)
{
	AGS* GS = GetWorld()->GetGameState<AGS>();
	return FRotator(GS->ZelieTransform[GS->Caches[CacheIndex]->CacheIndex].GetRotation());
}

FVector UConsumableAbility_TempAntiDot::GetCacheLocation(int32 CacheIndex)
{
	AGS* GS = GetWorld()->GetGameState<AGS>();
	return GS->ZelieTransform[GS->Caches[CacheIndex]->CacheIndex].GetLocation();
}

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
	TmpPlayer->UserView->RemoveIconFromPanel(IdentificatorIcon);
	DestroyNonNativeProperties();
}

bool UConsumableAbility_TempAntiDot::UseAbilityClient(AChel* Player)
{
	UConsumableAbility::UseAbilityClient(Player);
	return true;
}
