// Fill out your copyright notice in the Description page of Project Settings.


#include "Cache_Key.h"
#include "GS.h"

void ACache_Key::RemoveAndRefreshTimer()
{
	int NewIndex = ArrayIndex;
	AGS* GS = GetWorld()->GetGameState<AGS>();
	UE_LOG(LogTemp, Warning, TEXT("GS->Keys_IsAvaliable.Num() - %d"), GS->Keys_IsAvaliable.Num());
	UE_LOG(LogTemp, Warning, TEXT("ArrayIndex - %d"), ArrayIndex);
	while (!GS->Keys_IsAvaliable[NewIndex])
	{
		NewIndex = FMath::Rand() % GS->Keys_IsAvaliable.Num();
	}
	GS->Keys_IsAvaliable[ArrayIndex] = true;
	GS->Keys_IsAvaliable[NewIndex] = false;

	ArrayIndex = NewIndex;
	UE_LOG(LogTemp, Warning, TEXT("NewIndex - %d"), NewIndex);
	ReplaceMulticast(GS->Keys_Transform[NewIndex]);
	FTimerHandle FuzeTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(FuzeTimerHandle, this, &ACache_Key::Refresh, 12.f, false);
}

void ACache_Key::ReplaceMulticast_Implementation(FTransform NewTrans)
{
	SetActorTransform(NewTrans);
	SetActorEnableCollision(false);
	SetActorHiddenInGame(true);
}

void ACache_Key::RefreshMulticast_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Refreshed"));
	SetActorEnableCollision(true);
	SetActorHiddenInGame(false);
}

void ACache_Key::Refresh()
{
	RefreshMulticast();
}
