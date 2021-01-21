// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveCache.h"
#include "Chel.h"

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

bool AInteractiveCache::PickUpEventClient(AChel* Player)
{
	if (Player->KeysCount[CacheType] > 0 && bCanInterract)
	{
		bCanInterract = false;
		Player->UserView->ArrayCacheKey[CacheType]->SetText(FText::AsNumber(Player->KeysCount[CacheType] - 1));
		Player->KeysCount[CacheType]--;
		Player->UserView->E_Mark->SetVisibility(ESlateVisibility::Hidden);
		Player->LastInteractiveItem = nullptr;
		return true;
	}
	return false;
}

void AInteractiveCache::PickUpEventServer(AChel* Player)
{
	DisableEverywhere();
	Open();
}

void AInteractiveCache::OnLineTraced(AChel* Player)
{
	if (bCanInterract) {
		if (Player->KeysCount[CacheType] > 0) {
			if (!Player->UserView->E_Mark->IsVisible())
				Player->UserView->E_Mark->SetVisibility(ESlateVisibility::Visible);
		}
	}
}