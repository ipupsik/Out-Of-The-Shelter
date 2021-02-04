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
	for (int i = 0; i < Player->RAbilityStack.Num(); i++)
	{
		UConsumableAbility_TempAntiDot* Ability = Cast<UConsumableAbility_TempAntiDot>(Player->RAbilityStack[i]);
		if (Ability)
		{
			GetWorld()->GetTimerManager().ClearTimer(Ability->TimerHande);
			Player->RAbilityStackPop(i);
			break;
		}
	}

	StackIndex = Player->RAbilityStack.Num();
	Player->RAbilityStack.Add(this);
	Player->TempAntiDotEffect = 0.0f;
	TmpPlayer = Player;
	TimerHande = FTimerHandle();
	GetWorld()->GetTimerManager().SetTimer(TimerHande, this, &UConsumableAbility_TempAntiDot::EndEffect, Duration, false);
}

void UConsumableAbility_TempAntiDot::EndEffect()
{
	TmpPlayer->TempAntiDotEffect = 1.0f;
	TmpPlayer->RemoveIconFromPanel_Client(IdentificatorIcon);
	TmpPlayer->RAbilityStackPop(StackIndex);
}

bool UConsumableAbility_TempAntiDot::UseAbilityClient(AChel* Player)
{
	UConsumableAbility::UseAbilityClient(Player);
	return true;
}
