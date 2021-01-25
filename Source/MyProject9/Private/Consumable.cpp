// Fill out your copyright notice in the Description page of Project Settings.


#include "Consumable.h"
#include "Chel.h"

AConsumable::AConsumable() {
	Scene = CreateDefaultSubobject<USceneComponent>("Scene");
	Scene->SetupAttachment(RootComponent);

	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	Collision->SetupAttachment(Scene);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(Scene);
}

void AConsumable::PickUpEventServer(AChel* Player)
{
	Destroy();
}

bool AConsumable::PickUpEventClient(AChel* Player)
{
	if (Player->NewRAbility(Ability_class))
	{
		PlayPickUpSound();
		if (GetLocalRole() != ROLE_Authority)
			Destroy();
		return true;
	}
	else
	{
		PlayPickUpSound();
		Player->ReplaceRAbilityItem_Client(Ability_class);
		if (GetLocalRole() != ROLE_Authority)
			Destroy();
		return false;
	}
}
