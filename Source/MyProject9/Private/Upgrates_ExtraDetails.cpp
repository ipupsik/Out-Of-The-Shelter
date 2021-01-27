// Fill out your copyright notice in the Description page of Project Settings.


#include "Upgrates_ExtraDetails.h"
#include "Chel.h"

void AUpgrates_ExtraDetails::PickUpEventServer(AChel* Player)
{
	Destroy();
}

bool AUpgrates_ExtraDetails::PickUpEventClient(AChel* Player)
{
	if (Player->ExtraDetailsTimer == 0)
	{
		Player->ExtraDetailsTimer++;
		Player->AddExtraDetails();
	}
	else
		Player->ExtraDetailsTimer++;
	if (GetLocalRole() != ROLE_Authority)
	{
		Destroy();
	}
	return true;
}