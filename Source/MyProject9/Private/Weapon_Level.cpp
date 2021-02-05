// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon_Level.h"
#include "Weapon_Character.h"
#include "Chel.h"

AWeapon_Level::AWeapon_Level() {
	Amount = 1;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	Collision->SetupAttachment(Mesh);
}

bool AWeapon_Level::PickUpEventClient(AChel* Player) {
	PlayPickUpSound();
	return true;
}

void AWeapon_Level::ChangeAmount_Implementation(int32 NewAmount)
{
	Amount = NewAmount;
}

void AWeapon_Level::OnLineTraced(AChel* Player) {
	if (bCanInterract) {
		ToggleCustomDepth(true, Player);
		if (Player->CurrentWeapons[1]) {
			if (GetClass() == Player->CurrentWeapons[1]->WeaponLevelClass && Player->CurrentWeapons[1]->LeftAmmo == Player->CurrentWeapons[1]->MaxAmmo) {
				SetOutlineColor(1);
			}
			else {
				if (Player->GI->bIsEnabledPrompt)
					Player->UserView->PropmptTextInterract->SetText(PromptText);
				if (!Player->UserView->E_Mark->IsVisible()) {
					Player->UserView->E_Mark->SetVisibility(ESlateVisibility::Visible);
					if (Player->GI->bIsEnabledPrompt)
						Player->UserView->PropmptTextInterract->SetVisibility(ESlateVisibility::Visible);
				}
				SetOutlineColor(2);
			}
		}
		else {
			if (Player->GI->bIsEnabledPrompt)
				Player->UserView->PropmptTextInterract->SetText(PromptText);
			if (!Player->UserView->E_Mark->IsVisible()) {
				Player->UserView->E_Mark->SetVisibility(ESlateVisibility::Visible);
				if (Player->GI->bIsEnabledPrompt)
					Player->UserView->PropmptTextInterract->SetVisibility(ESlateVisibility::Visible);
			}
			SetOutlineColor(2);
		}
	}
}

void AWeapon_Level::PickUpEventServer(AChel* Player) { //Вызывается из PickUp серверовского чела
	if (Player->CurrentWeapons[1]) {
		if (Player->CurrentWeapons[1]->GetClass() == WeaponClass) {
			if (Player->CurrentWeapons[1]->LeftAmmo  == Player->CurrentWeapons[1]->MaxAmmo)
				return;
			if (Player->CurrentWeapons[1]->LeftAmmo + Amount <= Player->CurrentWeapons[1]->MaxAmmo) {
				Player->CurrentWeapons[1]->LeftAmmo += Amount;
				Player->ChangeAmmoClients(Player->CurrentWeapons[1]->LeftAmmo, 1);
				if (Player->CurrentIndex == 0 && Player->CurrentWeapons[0]->LeftAmmo == 0) {
					Player->SetWeaponToSlotMulticast(1);
				}
				else if (Player->CurrentIndex == 1) {
					Player->RefreshWidgetAmmoOwningClient(Player->CurrentWeapons[1]->LeftAmmo, Player->CurrentWeapons[1]->MaxAmmo, 1);
				}
				Destroy();
			}
			else {
				
				ChangeAmount(Amount - (Player->CurrentWeapons[1]->MaxAmmo - Player->CurrentWeapons[1]->LeftAmmo));
				Player->CurrentWeapons[1]->LeftAmmo = Player->CurrentWeapons[1]->MaxAmmo;

				if (Player->CurrentIndex == 0 && Player->CurrentWeapons[0]->LeftAmmo == 0) {
					Player->SetWeaponToSlotMulticast(1);
				}
				else if (Player->CurrentIndex == 1) {
					Player->RefreshWidgetAmmoOwningClient(Player->CurrentWeapons[1]->LeftAmmo, Player->CurrentWeapons[1]->MaxAmmo, 1);
				}
			}

		}
		else {
			if (Player->CurrentWeapons[1]->LeftAmmo > 0) {
				Player->CurrentWeapons[1]->DropItem();
			}
			UE_LOG(LogTemp, Warning, TEXT("I`m on Server and going to Multicast"));
			Player->CreateWeaponMulticast(WeaponClass, Amount, 1);
			if (GetLocalRole() == ROLE_Authority)
				Destroy();
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("I`m on Server and going to Multicast"));
		Player->CreateWeaponMulticast(WeaponClass, Amount, 1);
		if (GetLocalRole() == ROLE_Authority)
			Destroy();
	}
}