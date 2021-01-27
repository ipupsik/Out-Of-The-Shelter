// Fill out your copyright notice in the Description page of Project Settings.


#include "Upgrates_ExtraCacheKeys.h"
#include "Chel.h"

void AUpgrates_ExtraCacheKeys::PickUpEventServer(AChel* Player)
{
	Destroy();
}

bool AUpgrates_ExtraCacheKeys::PickUpEventClient(AChel* Player)
{
	if (Player->ExtraCacheKeysTimer == 0)
	{
		Player->ExtraCacheKeysTimer++;
		Player->AddExtraCacheKeys();
	}
	else
		Player->ExtraCacheKeysTimer++;
	if (GetLocalRole() != ROLE_Authority)
	{
		Destroy();
	}
	return true;
}