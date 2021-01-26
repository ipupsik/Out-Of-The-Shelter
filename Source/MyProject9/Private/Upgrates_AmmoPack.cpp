// Fill out your copyright notice in the Description page of Project Settings.


#include "Upgrates_AmmoPack.h"
#include "Chel.h"
#include "Weapon_Character.h"

void AUpgrates_AmmoPack::PickUpEventServer(AChel* Player) 
{
	Player->CurrentWeapons[0]->MaxAmmo += 5;
	Player->CurrentWeapons[0]->LeftAmmo += 5;
	Player->ChangeAmmoClients(Player->CurrentWeapons[0]->LeftAmmo, 0);
	Player->ChangeAmmoMaxClients(Player->CurrentWeapons[0]->MaxAmmo, 0);
	if (Player->CurrentIndex == 0)
	{
		Player->SetWeaponToSlotMulticast(0);
		Player->RefreshWidgetAmmoOwningClient(Player->CurrentWeapons[0]->LeftAmmo, Player->CurrentWeapons[0]->MaxAmmo, 0);
	}
	Destroy();
}

bool AUpgrates_AmmoPack::PickUpEventClient(AChel* Player) 
{
	if (GetLocalRole() != ROLE_Authority)
	{
		Destroy();
	}
	return true;
}