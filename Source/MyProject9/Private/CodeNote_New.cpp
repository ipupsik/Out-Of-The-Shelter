// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeNote_New.h"
#include "Chel.h"

ACodeNote_New::ACodeNote_New() {
	Scene = CreateDefaultSubobject<USceneComponent>("Scene");
	Scene->SetupAttachment(RootComponent);

	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	Collision->SetupAttachment(Scene);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(Scene);
}

bool ACodeNote_New::PickUpEventClient(AChel* Player)
{
	if (Player->Widget_Note->IsVisible())
	{
		Player->Widget_Note->SetVisibility(ESlateVisibility::Hidden);
		PlayPickUpSound();
		Player->bCanWalkingAndWatching = true;
	}
	else
	{
		Player->Widget_Note->ChangeText(Player->GS->CodeGenerator);
		Player->Widget_Note->SetVisibility(ESlateVisibility::Visible);
		PlayPickUpSound();
		Player->bCanWalkingAndWatching = false;
	}

	return false;
}

void ACodeNote_New::OnLineTraced(AChel* Player)
{
	if (bCanInterract) {
		ToggleCustomDepth(true, Player);
		if (Player->GI->bIsEnabledPrompt)
			Player->UserView->PropmptTextInterract->SetText(PromptText);
		if (!Player->UserView->E_Mark->IsVisible()) {
			Player->UserView->E_Mark->SetVisibility(ESlateVisibility::Visible);
			if (Player->GI->bIsEnabledPrompt)
				Player->UserView->PropmptTextInterract->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void ACodeNote_New::ToggleCustomDepth(bool NewIsOutliningNow, AChel* Player)
{
	if (bCanInterract) {
		if (this->IsOutliningNow != NewIsOutliningNow) {
			Mesh->SetRenderCustomDepth(NewIsOutliningNow);
			Mesh->MarkRenderStateDirty();
			this->IsOutliningNow = NewIsOutliningNow;
		}
	}
}
