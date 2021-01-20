// Fill out your copyright notice in the Description page of Project Settings.


#include "Consumable.h"

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
	Player->NewRAbility(Ability_class);
	Destroy();
	return true;
}
