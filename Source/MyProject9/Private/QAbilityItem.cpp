// Fill out your copyright notice in the Description page of Project Settings.


#include "QAbilityItem.h"
#include "QAbility.h"
#include "Chel.h"

AQAbilityItem::AQAbilityItem() {
	Scene = CreateDefaultSubobject<USceneComponent>("Scene");
	Scene->SetupAttachment(RootComponent);

	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	Collision->SetupAttachment(Scene);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(Scene);
}

void AQAbilityItem::PickUpEventServer(AChel* Player)
{
	if (Player->CurQAbility) {
		Player->ReplaceQAbilityItem(Player->CurQAbility->QAbilityitem_class, EnabledArrayIndex);
	}
	Player->CurQAbility = NewObject<UQAbility>(Player, QAbility_class);
	if (Player->IsPlayerOwner)
	{
		FSlateBrush NewBrush;
		NewBrush.SetResourceObject(Player->CurQAbility->Icon);
		Player->UserView->CurQSlot->AbilityImage->SetBrush(NewBrush);
	}
	Destroy();
}

bool AQAbilityItem::PickUpEventClient(AChel* Player)
{
	if (Player->CurQAbility) {
		if (Player->CurQAbility->GetClass() == QAbility_class)
			return false;
		if (Player->IsQAbilityUsing)
		{
			Player->IsQAbilityUsing = false;
			GetWorld()->GetTimerManager().ClearTimer(Player->QAbilityTimer);
			Player->CurQAbility->DeUseAbilityClient();
		}
		else if (Player->IsQAbilityRefreshing)
		{
			Player->IsQAbilityRefreshing = false;
			GetWorld()->GetTimerManager().ClearTimer(Player->QAbilityTimer);
		}
		Player->CurQAbility->RemoveFromRoot();
		Player->CurQAbility->ConditionalBeginDestroy();
		Player->CurQAbility = nullptr;
	}
	if (!Player->IsServerAuth) {
		Player->CurQAbility = NewObject<UQAbility>(Player, QAbility_class);
		FSlateBrush NewBrush;
		NewBrush.SetResourceObject(Player->CurQAbility->Icon);
		Player->UserView->CurQSlot->AbilityImage->SetBrush(NewBrush);
		Destroy();
	}
	return true;
}
