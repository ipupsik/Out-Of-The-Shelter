// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectableItem.h"
#include "Chel.h"

ACollectableItem::ACollectableItem() {
	
}

void ACollectableItem::ToggleCustomDepth(bool NewIsOutliningNow, AChel* Player) {
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
	if (bCanInterract && Player->UserView) {
		ToggleCustomDepth(true, Player);
		Player->UserView->PropmptTextInterract->SetText(PromptText);
		if (!Player->UserView->E_Mark->IsVisible()) {
			Player->UserView->E_Mark->SetVisibility(ESlateVisibility::Visible);
		}
		if(Player->GI->bIsEnabledPrompt)
				Player->UserView->PropmptTextInterract->SetVisibility(ESlateVisibility::Visible);
	}
}
