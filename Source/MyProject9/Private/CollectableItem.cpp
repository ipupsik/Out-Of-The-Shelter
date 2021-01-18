// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectableItem.h"

ACollectableItem::ACollectableItem() {
	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	Collision->SetupAttachment(RootComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(Collision);
}

void ACollectableItem::ToggleCustomDepth(bool IsOutliningNow) {
	if (bCanInterract) {
		Mesh->SetRenderCustomDepth(IsOutliningNow);
		Mesh->MarkRenderStateDirty();
	}
}

void ACollectableItem::SetOutlineColor(int32 ColorOutline) {
	if (bCanInterract && colorOutlineType != ColorOutline && ColorOutline != 0) {
		Mesh->SetCustomDepthStencilValue(ColorOutline);
		Mesh->MarkRenderStateDirty();
	}
}