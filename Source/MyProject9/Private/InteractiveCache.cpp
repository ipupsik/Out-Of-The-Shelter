// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveCache.h"

AInteractiveCache::AInteractiveCache()
{
	MainScene = CreateDefaultSubobject<USceneComponent>("MainScene");
	MainScene->SetupAttachment(RootComponent);

	Scene = CreateDefaultSubobject<USceneComponent>("Scene");
	Scene->SetupAttachment(MainScene);

	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	Collision->SetupAttachment(Scene);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(Scene);
}

void AInteractiveCache::DisableEverywhere_Implementation()
{
	bCanInterract = false;
}

void AInteractiveCache::ToggleCustomDepth(bool NewIsOutliningNow)
{
	
}

void AInteractiveCache::PickUpEventClient(AChel* Player)
{
	if (Player->KeysCount[CacheType] > 0 && bCanInterract)
	{
		bCanInterract = false;
		Player->UserView->ArrayCacheKey[CacheType]->SetText(FText::AsNumber(Player->KeysCount[CacheType] + 1));
		Player->KeysCount[CacheType]--;
	}
}

void AInteractiveCache::PickUpEventServer(AChel* Player)
{
	DisableEverywhere();
	Open();
}
