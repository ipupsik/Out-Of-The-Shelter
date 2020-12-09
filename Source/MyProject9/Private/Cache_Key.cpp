// Fill out your copyright notice in the Description page of Project Settings.


#include "Cache_Key.h"
#include "GS.h"

void ACache_Key::RemoveAndRefreshTimer()
{
	SetActorEnableCollision(false);
	SetActorHiddenInGame(true);

	int NewIndex = 0;
	AGS* GS = GetWorld()->GetGameState<AGS>();
	while (!GS->Keys_IsAvaliable[NewIndex])
	{
		NewIndex = FMath::Rand() % GS->Keys_IsAvaliable.Num();
	}
	GS->Keys_IsAvaliable[ArrayIndex] = true;
	GS->Keys_IsAvaliable[NewIndex] = false;

	ArrayIndex = NewIndex;

	SetActorTransform(GS->Keys_Transform[NewIndex]);

	FTimerHandle FuzeTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(FuzeTimerHandle, this, &ACache_Key::Refresh, 20, false);
}

void ACache_Key::Refresh()
{
	SetActorEnableCollision(true);
	SetActorHiddenInGame(false);
}
