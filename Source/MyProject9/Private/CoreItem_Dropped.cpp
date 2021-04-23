// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreItem_Dropped.h"
#include "Chel.h"

ACoreItem_Dropped::ACoreItem_Dropped() {
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	Collision->SetupAttachment(Mesh);
}

void ACoreItem_Dropped::PickUpEventServer(AChel* Player) {
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

bool ACoreItem_Dropped::PickUpEventClient(AChel * Player)
{
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
	if (Player->UserView)
		Player->UserView->ArraySwitcher[TypeItem]->SetActiveWidgetIndex(1);
	PlayPickUpSound();
	if (GetLocalRole() != ROLE_Authority)
		Destroy();
	return true;
}