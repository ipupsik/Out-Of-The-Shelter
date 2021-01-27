// Fill out your copyright notice in the Description page of Project Settings.


#include "ConAbility_ProjectileDamage.h"
#include "Chel.h"
#include "GS.h"
#include "InteractiveCache.h"

FVector UConAbility_ProjectileDamage::GetCacheScale3D(int32 CacheIndex)
{
	AGS* GS = GetWorld()->GetGameState<AGS>();
	return GS->ArmoryZelieTransform[GS->Caches[CacheIndex]->CacheIndex].GetScale3D();
}

FRotator UConAbility_ProjectileDamage::GetCacheRotation(int32 CacheIndex)
{
	AGS* GS = GetWorld()->GetGameState<AGS>();
	return FRotator(GS->ArmoryZelieTransform[GS->Caches[CacheIndex]->CacheIndex].GetRotation());
}

FVector UConAbility_ProjectileDamage::GetCacheLocation(int32 CacheIndex)
{
	AGS* GS = GetWorld()->GetGameState<AGS>();
	return GS->ArmoryZelieTransform[GS->Caches[CacheIndex]->CacheIndex].GetLocation();
}

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
	TmpPlayer->UserView->RemoveIconFromPanel(IdentificatorIcon);
	DestroyNonNativeProperties();
}

bool UConAbility_ProjectileDamage::UseAbilityClient(AChel* Player)
{
	UConsumableAbility::UseAbilityClient(Player);
	return true;
}
