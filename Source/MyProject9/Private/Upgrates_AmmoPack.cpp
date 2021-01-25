// Fill out your copyright notice in the Description page of Project Settings.


#include "Upgrates_AmmoPack.h"
#include "Chel.h"
#include "Weapon_Character.h"

void AUpgrates_AmmoPack::PickUpEventServer(AChel* Player) 
{
	Player->CurrentWeapons[0]->MaxAmmo += 5;
	Destroy();
}

bool AUpgrates_AmmoPack::PickUpEventClient(AChel* Player) 
{
	Player->UserView->AmmoMax->SetText(FText::AsNumber(Player->MaxAmmoCount + 5));
	if (GetLocalRole() != ROLE_Authority)
	{
		Player->CurrentWeapons[0]->MaxAmmo += 5;
		Destroy();
	}
	return true;
}