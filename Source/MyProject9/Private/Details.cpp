// Fill out your copyright notice in the Description page of Project Settings.


#include "Details.h"
#include "Chel.h"
#include "GS.h"

ADetails::ADetails() {
	Scene = CreateDefaultSubobject<USceneComponent>("Scene");
	Scene->SetupAttachment(RootComponent);

	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	Collision->SetupAttachment(Scene);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(Scene);
}


void ADetails::PickUpEventServer(AChel* Player) {
	PlayPickUpSound();
	RemoveAndRefreshTimer();
}

bool ADetails::PickUpEventClient(AChel* Player) {
	Player->UserView->Details->SetText(FText::AsNumber(Player->AmountDetails + 1));
	Player->AmountDetails++;
	PlayPickUpSound();
	if (GetLocalRole() != ROLE_Authority) {
		SetActorEnableCollision(false);
		SetActorHiddenInGame(true);
	}
	return true;
}

void ADetails::RemoveAndRefreshTimer()
{
	int NewIndex = EnabledArrayIndex;
	AGS* GS = GetWorld()->GetGameState<AGS>();
	while (!GS->Details_IsAvaliable[NewIndex])
	{
		NewIndex++;
		if (NewIndex >= GS->Details_IsAvaliable.Num())
			NewIndex = 0;
	}
	GS->Details_IsAvaliable[EnabledArrayIndex] = true;
	GS->Details_IsAvaliable[NewIndex] = false;

	EnabledArrayIndex = NewIndex;
	ReplaceMulticast(GS->Details_Transform[NewIndex]);
	FTimerHandle FuzeTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(FuzeTimerHandle, this, &ADetails::Refresh, 12.f, false);
}

void ADetails::ReplaceMulticast_Implementation(FTransform NewTrans)
{
	SetActorTransform(NewTrans);
	SetActorEnableCollision(false);
	SetActorHiddenInGame(true);
}

void ADetails::RefreshMulticast_Implementation()
{
	SetActorEnableCollision(true);
	SetActorHiddenInGame(false);
}

void ADetails::Refresh()
{
	RefreshMulticast();
}
