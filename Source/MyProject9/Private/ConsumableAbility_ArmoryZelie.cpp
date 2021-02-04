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
	for (int i = 0; i < Player->RAbilityStack.Num(); i++)
	{
		UConsumableAbility_ArmoryZelie* Ability = Cast<UConsumableAbility_ArmoryZelie>(Player->RAbilityStack[i]);
		if (Ability)
		{
			Player->RAbilityStackPop(i);
			break;
		}
	}
	Player->CreateParticleImmortal();
	StackIndex = Player->RAbilityStack.Num();
	Player->RAbilityStack.Add(this);
	Player->IsNowInvisible = true;
	TmpPlayer = Player;
	TimerHande = FTimerHandle();
	GetWorld()->GetTimerManager().SetTimer(TimerHande, this, &UConsumableAbility_ArmoryZelie::EndEffect, Duration, false);
}

void UConsumableAbility_ArmoryZelie::EndEffect()
{
	TmpPlayer->DeleteParticleImmortal();
	TmpPlayer->ArmoryZelieEffect = 1.0f;
	TmpPlayer->RemoveIconFromPanel_Client(IdentificatorIcon);
	TmpPlayer->RAbilityStackPop(StackIndex);
}

bool UConsumableAbility_ArmoryZelie::UseAbilityClient(AChel* Player)
{
	UConsumableAbility::UseAbilityClient(Player);
	return true;
}