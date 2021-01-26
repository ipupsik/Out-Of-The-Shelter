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
	Player->HaveSpecialAmmo = true;
	if (GetLocalRole() != ROLE_Authority)
	{
		Destroy();
	}
	return true;
}
