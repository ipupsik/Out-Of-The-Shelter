// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreItem.h"
#include "Chel.h"

ACoreItem::ACoreItem() {
	Scene = CreateDefaultSubobject<USceneComponent>("Scene");
	Scene->SetupAttachment(RootComponent);

	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	Collision->SetupAttachment(Scene);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(Scene);
}

void ACoreItem::PickUpEventServer(AChel* Player) {
	PlayPickUpSound();
	Player->DoesHave[TypeItem] = true;
	Destroy();
}

bool ACoreItem::PickUpEventClient(AChel * Player)
{
	Player->UserView->ArraySwitcher[TypeItem]->SetActiveWidgetIndex(1);
	PlayPickUpSound();
	if (GetLocalRole() != ROLE_Authority)
		Destroy();
	return true;
}