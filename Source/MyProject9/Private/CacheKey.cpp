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
	int NewIndex = ArrayIndex;
	AGS* GS = GetWorld()->GetGameState<AGS>();
	while (!GS->Keys_IsAvaliable[NewIndex])
	{
		NewIndex = FMath::Rand() % GS->Keys_IsAvaliable.Num();
	}
	GS->Keys_IsAvaliable[ArrayIndex] = true;
	GS->Keys_IsAvaliable[NewIndex] = false;

	ArrayIndex = NewIndex;
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
