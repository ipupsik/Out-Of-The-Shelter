// Fill out your copyright notice in the Description page of Project Settings.


#include "Upgrates_Shields.h"
#include "Chel.h"

void AUpgrates_Shields::PickUpEventServer(AChel* Player)
{
	Player->ShieldsCount++;
	Destroy();
}

bool AUpgrates_Shields::PickUpEventClient(AChel* Player)
{
	PlayPickUpSound();
	if (GetLocalRole() != ROLE_Authority)
	{
		Player->ShieldsCount++;
		Destroy();
	}
	return true;
}