// Fill out your copyright notice in the Description page of Project Settings.


#include "GM.h"
#include "BP_PlayerController.h"
#include "Kismet/GameplayStatics.h"

void AGM::Respawn()
{
	TArray<AActor*>Players;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABP_PlayerController::StaticClass(), Players);
	for (int i = 0; i < Players.Num(); i++)
	{
		ABP_PlayerController* Player = Cast<ABP_PlayerController>(Players[i]);
		if (!Player->IsHost)
		{
			RestartPlayer(Player);
		}
	}

	for (int i = 0; i < Players.Num(); i++)
	{
		ABP_PlayerController* Player = Cast<ABP_PlayerController>(Players[i]);
		if (Player->IsHost)
		{
			RestartPlayer(Player);
		}
	}
}