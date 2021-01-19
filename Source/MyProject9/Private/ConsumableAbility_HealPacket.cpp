// Fill out your copyright notice in the Description page of Project Settings.


#include "ConsumableAbility_HealPacket.h"
#include "Chel.h"

UConsumableAbility_HealPacket::UConsumableAbility_HealPacket()
{
	ConstructorHelpers::FObjectFinder<UTexture2D> BarFillObj(TEXT("/Game/Assets/Images/circle-cropped__1_"));
	Icon = BarFillObj.Object;
	MaxCountToStack = 3;
}

void UConsumableAbility_HealPacket::UseAbilityClient(AChel* Player)
{
	
}

void UConsumableAbility_HealPacket::UseAbilityServer(AChel* Player)
{
	Player->Health = 0;
}