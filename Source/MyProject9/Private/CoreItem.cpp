// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreItem.h"

ACoreItem::ACoreItem() {

}

void ACoreItem::PickUpEventServer(AChel* Player) {
	PlayPickUpSound();
	Player->DoesHave[TypeItem] = true;
	Destroy();
}

void ACoreItem::PickUpEventClient(AChel * Player)
{
	Player->UserView->ArraySwitcher[TypeItem]->SetActiveWidgetIndex(1);
}
