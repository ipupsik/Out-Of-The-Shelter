// Fill out your copyright notice in the Description page of Project Settings.


#include "QAbility_Rentgen.h"
#include "InteractiveCache.h"
#include "Chel.h"
#include "CoreItem.h"

FVector UQAbility_Rentgen::GetCacheScale3D(int32 CacheIndex)
{
	AGS* MyGS = GetWorld()->GetGameState<AGS>();
	return MyGS->RentgenGlassTransform[MyGS->Caches[CacheIndex]->CacheIndex].GetScale3D();
}

FRotator UQAbility_Rentgen::GetCacheRotation(int32 CacheIndex)
{
	AGS* MyGS = GetWorld()->GetGameState<AGS>();
	return FRotator(MyGS->RentgenGlassTransform[MyGS->Caches[CacheIndex]->CacheIndex].GetRotation());
}

FVector UQAbility_Rentgen::GetCacheLocation(int32 CacheIndex)
{
	AGS* MyGS = GetWorld()->GetGameState<AGS>();
	return MyGS->RentgenGlassTransform[MyGS->Caches[CacheIndex]->CacheIndex].GetLocation();
}

bool UQAbility_Rentgen::UseAbilityClient(AChel* Player)
{
	Player->IsRentgenRender = true;
	Player->RentgentOnSound();
	TArray<AActor*>RentgenItems;
	Player->SenseCollision->GetOverlappingActors(RentgenItems, ACoreItem::StaticClass());
	for (auto& it : RentgenItems)
	{
		Cast<ACoreItem>(it)->ToggleCustomDepth(true, Player);
	}
	Player->IsQAbilityUsing = true;
	Player->QAbilityTimer = FTimerHandle();
	TmpPlayer = Player;
	GetWorld()->GetTimerManager().SetTimer(Player->QAbilityTimer, this, &UQAbility_Rentgen::DeUseAbilityClient, Duration, false);
	return false;
}

void UQAbility_Rentgen::DeUseAbilityClient()
{
	TmpPlayer->IsRentgenRender = false;
	TmpPlayer->RentgentOffSound();
	TArray<AActor*>RentgenItems;
	TmpPlayer->SenseCollision->GetOverlappingActors(RentgenItems, ACoreItem::StaticClass());
	for (auto& it : RentgenItems)
	{
		Cast<ACoreItem>(it)->ToggleCustomDepth(false, TmpPlayer);
	}
	if (TmpPlayer->IsQAbilityUsing) {
		TmpPlayer->IsQAbilityUsing = false;
		TmpPlayer->IsQAbilityRefreshing = true;
		TmpPlayer->QAbilityTimer = FTimerHandle();
		GetWorld()->GetTimerManager().SetTimer(TmpPlayer->QAbilityTimer, TmpPlayer, &AChel::QAbilityEnableAvaliable, DurationAvaliable, false);
	}
}