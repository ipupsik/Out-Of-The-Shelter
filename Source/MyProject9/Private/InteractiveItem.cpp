// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveItem.h"

// Sets default values
AInteractiveItem::AInteractiveItem()
{
	colorOutlineType = -1;
	bCanInterract = true;
}

void AInteractiveItem::ToggleCustomDepth(bool NewIsOutliningNow, AChel* Player)
{
	if (bCanInterract) {

	}
}

void AInteractiveItem::SetOutlineColor(int32 ColorOutline)
{
}

void AInteractiveItem::PickUpEventServer(AChel * Player)
{
}

bool AInteractiveItem::PickUpEventClient(AChel * Player)
{
	return true;
}

void AInteractiveItem::OnLineTraced(AChel* Player)
{
}

bool AInteractiveItem::PickUpEventReleaseClient(AChel* Player) {
	return false;
}

void AInteractiveItem::PickUpEventReleaseServer(AChel* Player)
{

}