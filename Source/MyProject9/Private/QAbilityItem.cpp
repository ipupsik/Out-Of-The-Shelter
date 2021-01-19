// Fill out your copyright notice in the Description page of Project Settings.


#include "QAbilityItem.h"
#include "QAbility.h"

void AQAbilityItem::PickUpEventServer(AChel* Player)
{
	if (Player->CurQAbility) {
		Player->ReplaceQAbilityItem(Player->CurQAbility->QAbilityitem_class, EnabledArrayIndex);
	}
	Destroy();
}

void AQAbilityItem::PickUpEventClient(AChel* Player)
{
	Player->CurQAbility = NewObject<UQAbility>(Player, QAbility_class);
}
