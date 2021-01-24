// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonClick.h"
#include "Chel.h"

AButtonClick::AButtonClick()
{
	Scene = CreateDefaultSubobject<USceneComponent>("Scene");
	Scene->SetupAttachment(RootComponent);

	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	Collision->SetupAttachment(Scene);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(Scene);

	Decal = CreateDefaultSubobject<UDecalComponent>("Decal");
	Decal->SetupAttachment(Scene);
}

void AButtonClick::ToggleCustomDepth(bool NewIsOutliningNow)
{
	if (this->IsOutliningNow != NewIsOutliningNow) {
		Mesh->SetRenderCustomDepth(NewIsOutliningNow);
		Mesh->MarkRenderStateDirty();
		this->IsOutliningNow = NewIsOutliningNow;
	}
}

void AButtonClick::PickUpEventServer(AChel* Player)
{
	if (bCanInterract) {
		if (ButtonType <= 9) {
			if (Player->GS->NumbersOnPanel.Num() <= 4) {
				Player->GS->AddNumToTerminal(ButtonType);
				bCanInterract = false;
				ButtonPressAnimation();
			}
		}
		else {
			if (ButtonType == 10) {
				if (Player->GS->NumbersOnPanel.Num() > 0) {
					Player->GS->DeleteLastNumber();
					bCanInterract = false;
					ButtonPressAnimation();
				}
			}
			else
			{
				Player->GS->CheckCode(Player->Index);
				bCanInterract = false;
				ButtonPressAnimation();
			}
		}
	}
}

bool AButtonClick::PickUpEventClient(AChel* Player)
{
	if (Player->GS->IsShelterAvaliable)
	{
		return true;
	}
	return false;
}

void AButtonClick::OnLineTraced(AChel* Player)
{
	if (bCanInterract && Player->GS->IsShelterAvaliable) {
		ToggleCustomDepth(true);
		if (Player->GI->bIsEnabledPrompt)
			Player->UserView->PropmptTextInterract->SetText(PromptText);
		if (!Player->UserView->E_Mark->IsVisible()) {
			Player->UserView->E_Mark->SetVisibility(ESlateVisibility::Visible);
			if (Player->GI->bIsEnabledPrompt)
				Player->UserView->PropmptTextInterract->SetVisibility(ESlateVisibility::Visible);
		}
	}
}
