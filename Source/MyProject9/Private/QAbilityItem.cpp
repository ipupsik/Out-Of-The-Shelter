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
		Player->CurQAbility->ConditionalBeginDestroy();
	}
	Player->CurQAbility = NewObject<UQAbility>(Player, QAbility_class);
	Destroy();
}

bool AQAbilityItem::PickUpEventClient(AChel* Player)
{
	if (Player->CurQAbility) {
		if (Player->CurQAbility->GetClass() == QAbility_class)
			return false;
		Player->CurQAbility->ConditionalBeginDestroy();
	}
	UQAbility* TempAbility = NewObject<UQAbility>(Player, QAbility_class);
	if (GetLocalRole() != ROLE_Authority)
		Player->CurQAbility = TempAbility;
	FSlateBrush NewBrush;
	NewBrush.SetResourceObject(TempAbility->Icon);
	Player->UserView->CurQSlot->AbilityImage->SetBrush(NewBrush);
	return true;
}
