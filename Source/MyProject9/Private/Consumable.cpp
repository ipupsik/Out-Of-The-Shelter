// Fill out your copyright notice in the Description page of Project Settings.


#include "Consumable.h"

AConsumable::AConsumable() {
}

void AConsumable::PickUpEventServer(AChel* Player)
{
	Destroy();
}

void AConsumable::PickUpEventClient(AChel* Player)
{
	Player->NewRAbility(Ability_class);
	Destroy();
}
