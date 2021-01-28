// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreItem.h"
#include "Chel.h"
#include "Kismet/GameplayStatics.h"

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
	TArray<AActor*>Players;
	UGameplayStatics::GetAllActorsOfClass(Player->World, AChel::StaticClass(), Players);
	for (auto& itPlayer : Players) {
		AChel* TmpPlayer = Cast<AChel>(itPlayer);
		TmpPlayer->PickUpCoreItem(TypeItem, Player->GS->NickNames[Player->Index]);
	}
	Destroy();
}

bool ACoreItem::PickUpEventClient(AChel * Player)
{
	Player->UserView->ArraySwitcher[TypeItem]->SetActiveWidgetIndex(1);
	switch (TypeItem)
	{
	case 0:
	{
		Player->MainExis_Canalizacia->Mesh->SetRenderCustomDepth(true);
		Player->MainExis_Canalizacia->Mesh->MarkRenderStateDirty();
		break;
	}
	case 1:
	{
		Player->MainExis_Shelter->Mesh->SetRenderCustomDepth(true);
		Player->MainExis_Shelter->Mesh->MarkRenderStateDirty();
		break;
	}
	case 2:
	{
		Player->MainExis_Ventilacia->Mesh->SetRenderCustomDepth(true);
		Player->MainExis_Ventilacia->Mesh->MarkRenderStateDirty();
		break;
	}
	}
	PlayPickUpSound();
	if (GetLocalRole() != ROLE_Authority)
		Destroy();
	return true;
}