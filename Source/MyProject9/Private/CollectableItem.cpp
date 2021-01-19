// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectableItem.h"

ACollectableItem::ACollectableItem() {
<<<<<<< HEAD

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(Collision);

	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	RootComponent = Collision;

	Collision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
=======
	Scene = CreateDefaultSubobject<USceneComponent>("Scene");
	Scene->SetupAttachment(RootComponent);

	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	Collision->SetupAttachment(Scene);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(Scene);
>>>>>>> 80dff1d7d34d67d606e1606dc3c49a7a3b796c47
}

void ACollectableItem::ToggleCustomDepth(bool NewIsOutliningNow) {
	if (bCanInterract) {
		if (this->IsOutliningNow != NewIsOutliningNow) {
			Mesh->SetRenderCustomDepth(NewIsOutliningNow);
			Mesh->MarkRenderStateDirty();
			this->IsOutliningNow = NewIsOutliningNow;
		}
	}
}

void ACollectableItem::SetOutlineColor(int32 ColorOutline) {
	if (bCanInterract && colorOutlineType != ColorOutline && ColorOutline != 0) {
		Mesh->SetCustomDepthStencilValue(ColorOutline);
		Mesh->MarkRenderStateDirty();
	}
}