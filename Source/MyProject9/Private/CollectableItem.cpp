// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectableItem.h"

ACollectableItem::ACollectableItem() {

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(Collision);

	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	RootComponent = Collision;

	Collision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
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