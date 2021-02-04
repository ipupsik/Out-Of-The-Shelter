// Fill out your copyright notice in the Description page of Project Settings.


#include "ConsumableAbility_Invisible.h"
#include "Chel.h"
#include "GS.h"
#include "InteractiveCache.h"

FVector UConsumableAbility_Invisible::GetCacheScale3D(int32 CacheIndex)
{
	AGS* GS = GetWorld()->GetGameState<AGS>();
	return GS->ZelieTransform[GS->Caches[CacheIndex]->CacheIndex].GetScale3D();
}

FRotator UConsumableAbility_Invisible::GetCacheRotation(int32 CacheIndex)
{
	AGS* GS = GetWorld()->GetGameState<AGS>();
	return FRotator(GS->ZelieTransform[GS->Caches[CacheIndex]->CacheIndex].GetRotation());
}

FVector UConsumableAbility_Invisible::GetCacheLocation(int32 CacheIndex)
{
	AGS* GS = GetWorld()->GetGameState<AGS>();
	return GS->ZelieTransform[GS->Caches[CacheIndex]->CacheIndex].GetLocation();
}

void UConsumableAbility_Invisible::UseAbilityServer(AChel* Player)
{
	if (!Player->IsNowInvisible)
		Player->InvisibleEverywhere();
	else
	{
		for (int i = 0; i < Player->RAbilityStack.Num(); i++)
		{
			UConsumableAbility_Invisible* Ability = Cast<UConsumableAbility_Invisible>(Player->RAbilityStack[i]);
			if (Ability)
			{
				Player->RAbilityStackPop(i);
				break;
			}
		}
	}
	StackIndex = Player->RAbilityStack.Num();
	Player->RAbilityStack.Add(this);
	Player->IsNowInvisible = true;
	TmpPlayer = Player;
	TimerHande = FTimerHandle();
	GetWorld()->GetTimerManager().SetTimer(TimerHande, this, &UConsumableAbility_Invisible::InvisibleEnd, Duration, false);
}

bool UConsumableAbility_Invisible::UseAbilityClient(AChel* Player)
{
	UConsumableAbility::UseAbilityClient(Player);
	return true;
}

void UConsumableAbility_Invisible::InvisibleEnd()
{
	TmpPlayer->IsNowInvisible = false;
	TmpPlayer->ReverceInvisibleEverywhere();
	TmpPlayer->RAbilityStackPop(StackIndex);
}