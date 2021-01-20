// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectableItem.h"

ACollectableItem::ACollectableItem() {
	
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
		colorOutlineType = ColorOutline;
	}
}

void ACollectableItem::OnLineTraced(AChel* Player)
{
	if (bCanInterract) {
		ToggleCustomDepth(true);
		if (Player->UserView->E_Mark->IsVisible())
			Player->UserView->E_Mark->SetVisibility(ESlateVisibility::Visible);
	}
}
