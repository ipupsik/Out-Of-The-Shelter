// Fill out your copyright notice in the Description page of Project Settings.


#include "CacheKey.h"
#include "Chel.h"
#include "GS.h"

ACacheKey::ACacheKey() {
	Scene = CreateDefaultSubobject<USceneComponent>("Scene");
	Scene->SetupAttachment(RootComponent);

	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	Collision->SetupAttachment(Scene);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(Scene);
}


void ACacheKey::PickUpEventServer(AChel* Player) {
	PlayPickUpSound();
	RemoveAndRefreshTimer();
}

bool ACacheKey::PickUpEventClient(AChel* Player) {
	Player->UserView->ArrayCacheKey[TypeKey]->SetText(FText::AsNumber(Player->KeysCount[TypeKey] + 1));
	Player->KeysCount[TypeKey]++;
	PlayPickUpSound();
	if (GetLocalRole() != ROLE_Authority) {
		SetActorEnableCollision(false);
		SetActorHiddenInGame(true);
	}
	return true;
}

void ACacheKey::RemoveAndRefreshTimer()
{
	int NewIndex = EnabledArrayIndex;
	AGS* GS = GetWorld()->GetGameState<AGS>();
	while (!GS->Keys_IsAvaliable[NewIndex])
	{
		NewIndex++;
		if (NewIndex >= GS->Keys_IsAvaliable.Num())
			NewIndex = 0;
	}
	GS->Keys_IsAvaliable[EnabledArrayIndex] = true;
	GS->Keys_IsAvaliable[NewIndex] = false;

	EnabledArrayIndex = NewIndex;
	ReplaceMulticast(GS->Keys_Transform[NewIndex]);
	FTimerHandle FuzeTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(FuzeTimerHandle, this, &ACacheKey::Refresh, 12.f, false);
}

void ACacheKey::ReplaceMulticast_Implementation(FTransform NewTrans)
{
	SetActorTransform(NewTrans);
	SetActorEnableCollision(false);
	SetActorHiddenInGame(true);
}

void ACacheKey::RefreshMulticast_Implementation()
{
	SetActorEnableCollision(true);
	SetActorHiddenInGame(false);
}

void ACacheKey::Refresh()
{
	RefreshMulticast();
}
