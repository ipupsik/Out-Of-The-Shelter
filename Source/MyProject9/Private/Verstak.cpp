// Fill out your copyright notice in the Description page of Project Settings.


#include "Verstak.h"

AVerstak::AVerstak() {
	Scene = CreateDefaultSubobject<USceneComponent>("Scene");
	Scene->SetupAttachment(RootComponent);

	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	Collision->SetupAttachment(Scene);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(Scene);
}

bool AVerstak::PickUpEventClient(AChel * Player)
{
	Player->VerstakViewWidget->SetVisibility(ESlateVisibility::Visible);
	Player->VerstakViewWidget->CallRefreshItemsBlueprint();
	Player->MyController->bShowMouseCursor = true;
	return false;
}

void AVerstak::PickUpEventServer(AChel * Player)
{
}

void AVerstak::OnLineTraced(AChel * Player)
{
	if (bCanInterract) {
		ToggleCustomDepth(true);
		if (!Player->UserView->E_Mark->IsVisible())
			Player->UserView->E_Mark->SetVisibility(ESlateVisibility::Visible);
	}
}

void AVerstak::ToggleCustomDepth(bool NewIsOutliningNow) {
	if (bCanInterract) {
		if (this->IsOutliningNow != NewIsOutliningNow) {
			Mesh->SetRenderCustomDepth(NewIsOutliningNow);
			Mesh->MarkRenderStateDirty();
			this->IsOutliningNow = NewIsOutliningNow;
		}
	}
}

