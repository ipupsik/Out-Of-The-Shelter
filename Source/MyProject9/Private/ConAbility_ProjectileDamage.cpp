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
	for (int i = 0; i < Player->RAbilityStack.Num(); i++)
	{
		UConAbility_ProjectileDamage* Ability = Cast<UConAbility_ProjectileDamage>(Player->RAbilityStack[i]);
		if (Ability)
		{
			GetWorld()->GetTimerManager().ClearTimer(Ability->TimerHande);
			Player->RAbilityStackPop(i);
			break;
		}
	}

	StackIndex = Player->RAbilityStack.Num();
	Player->RAbilityStack.Add(this);
	Player->ProjectileDamageEffect =2.f;
	TmpPlayer = Player;
	TimerHande = FTimerHandle();
	GetWorld()->GetTimerManager().SetTimer(TimerHande, this, &UConAbility_ProjectileDamage::EndEffect, Duration, false);
}

void UConAbility_ProjectileDamage::EndEffect()
{
	TmpPlayer->ProjectileDamageEffect = 1.0f;
	TmpPlayer->RemoveIconFromPanel_Client(IdentificatorIcon);
	TmpPlayer->RAbilityStackPop(StackIndex);
}

bool UConAbility_ProjectileDamage::UseAbilityClient(AChel* Player)
{
	UConsumableAbility::UseAbilityClient(Player);
	return true;
}
