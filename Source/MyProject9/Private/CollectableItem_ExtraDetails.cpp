// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectableItem_ExtraDetails.h"
#include "Chel.h"

ACollectableItem_ExtraDetails::ACollectableItem_ExtraDetails() {
	Scene = CreateDefaultSubobject<USceneComponent>("Scene");
	Scene->SetupAttachment(RootComponent);

	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	Collision->SetupAttachment(Scene);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(Scene);

	Mesh2 = CreateDefaultSubobject<UStaticMeshComponent>("Mesh2");
	Mesh2->SetupAttachment(Scene);

	Mesh3 = CreateDefaultSubobject<UStaticMeshComponent>("Mesh3");
	Mesh3->SetupAttachment(Scene);

	Amount = 1 + FMath::Rand() % 10;
}

void ACollectableItem_ExtraDetails::ToggleCustomDepth(bool NewIsOutliningNow, AChel* Player)
{
	if (bCanInterract) {
		if (this->IsOutliningNow != NewIsOutliningNow) {
			Mesh->SetRenderCustomDepth(NewIsOutliningNow);
			Mesh->MarkRenderStateDirty();
			Mesh2->SetRenderCustomDepth(NewIsOutliningNow);
			Mesh2->MarkRenderStateDirty();
			Mesh3->SetRenderCustomDepth(NewIsOutliningNow);
			Mesh3->MarkRenderStateDirty();
			this->IsOutliningNow = NewIsOutliningNow;
		}
	}
}

void ACollectableItem_ExtraDetails::PickUpEventServer(AChel* Player)
{
	Destroy();
}

bool ACollectableItem_ExtraDetails::PickUpEventClient(AChel* Player)
{
	Player->AmountDetails += Amount;
	Player->UserView->Details->SetText(FText::AsNumber(Player->AmountDetails));
	if (GetLocalRole() != ROLE_Authority)
	{
		Destroy();
	}
	return true;
}