// Fill out your copyright notice in the Description page of Project Settings.


#include "ConsumableAbility_HealPacket.h"
#include "Chel.h"
#include "GS.h"
#include "InteractiveCache.h"

UConsumableAbility_HealPacket::UConsumableAbility_HealPacket()
{
	ConstructorHelpers::FObjectFinder<UTexture2D> BarFillObj(TEXT("/Game/Assets/Images/circle-cropped__1_"));
	Icon = BarFillObj.Object;
}

bool UConsumableAbility_HealPacket::UseAbilityClient(AChel* Player)
{
	UConsumableAbility::UseAbilityClient(Player);
	return true;
}

void UConsumableAbility_HealPacket::UseAbilityServer(AChel* Player)
{
	Player->Health = 0;
}

FVector UConsumableAbility_HealPacket::GetCacheScale3D(int32 CacheIndex)
{
	AGS* GS = GetWorld()->GetGameState<AGS>();
	return GS->HealPacketTransform[GS->Caches[CacheIndex]->CacheIndex].GetScale3D();
}

FRotator UConsumableAbility_HealPacket::GetCacheRotation(int32 CacheIndex)
{
	AGS* GS = GetWorld()->GetGameState<AGS>();
	return FRotator(GS->HealPacketTransform[GS->Caches[CacheIndex]->CacheIndex].GetRotation());
}

FVector UConsumableAbility_HealPacket::GetCacheLocation(int32 CacheIndex)
{
	AGS* GS = GetWorld()->GetGameState<AGS>();
	return GS->HealPacketTransform[GS->Caches[CacheIndex]->CacheIndex].GetLocation();
}