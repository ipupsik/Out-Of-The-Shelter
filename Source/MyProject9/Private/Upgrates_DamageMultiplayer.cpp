// Fill out your copyright notice in the Description page of Project Settings.


#include "Upgrates_DamageMultiplayer.h"
#include "Chel.h"

void AUpgrates_DamageMultiplayer::PickUpEventServer(AChel* Player)
{
	Player->StoneDamageBuffCount++;
	Destroy();
}

bool AUpgrates_DamageMultiplayer::PickUpEventClient(AChel* Player)
{
	if (GetLocalRole() != ROLE_Authority)
	{
		Destroy();
	}
	return true;
}
