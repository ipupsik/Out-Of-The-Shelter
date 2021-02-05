// Fill out your copyright notice in the Description page of Project Settings.


#include "Upgrates_Special.h"
#include "Chel.h"
#include "Weapon_Character.h"

void AUpgrates_Special::PickUpEventServer(AChel* Player)
{
	Player->HaveSpecialAmmo = true;
	if (Player->CurrentWeapons[1]) {
		Player->CurrentWeapons[1]->MaxAmmo += Player->CurrentWeapons[1]->ExtraAmountAmmo;
		Player->ChangeAmmoMaxClients(Player->CurrentWeapons[1]->MaxAmmo, 1);
		if (Player->CurrentIndex == 1)
		{
			Player->RefreshWidgetAmmoOwningClient(Player->CurrentWeapons[1]->LeftAmmo, Player->CurrentWeapons[1]->MaxAmmo, 1);
		}
	}
	Destroy();
}

bool AUpgrates_Special::PickUpEventClient(AChel* Player)
{
	if (!Player->HaveSpecialAmmo) {
		Player->HaveSpecialAmmo = true;
		PlayPickUpSound();
		if (GetLocalRole() != ROLE_Authority)
		{
			Destroy();
		}
		return true;
	}
	else
		return false;
}

void AUpgrates_Special::OnLineTraced(AChel* Player)
{
	if(!Player->HaveSpecialAmmo) {
		SetOutlineColor(2);
		ToggleCustomDepth(true, Player);
		if(Player->GI->bIsEnabledPrompt && Player->UserView->PropmptTextInterract->GetText().ToString() != PromptText.ToString())
			Player->UserView->PropmptTextInterract->SetText(PromptText);
		if (!Player->UserView->E_Mark->IsVisible()) {
			Player->UserView->E_Mark->SetVisibility(ESlateVisibility::Visible);
			if (Player->GI->bIsEnabledPrompt)
				Player->UserView->PropmptTextInterract->SetVisibility(ESlateVisibility::Visible);
		}
	}
	else {
		SetOutlineColor(1);
		ToggleCustomDepth(true, Player);
		if (Player->GI->bIsEnabledPrompt && Player->UserView->PropmptTextInterract->GetText().ToString() != BadOutlineText.ToString())
			Player->UserView->PropmptTextInterract->SetText(BadOutlineText);
		if (!Player->UserView->E_Mark->IsVisible()) {
			Player->UserView->E_Mark->SetVisibility(ESlateVisibility::Hidden);
			if (Player->GI->bIsEnabledPrompt)
				Player->UserView->PropmptTextInterract->SetVisibility(ESlateVisibility::Visible);
		}
	}
}