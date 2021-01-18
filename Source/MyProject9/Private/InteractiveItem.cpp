// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveItem.h"

// Sets default values
AInteractiveItem::AInteractiveItem()
{
	colorOutlineType = 1;
	bCanInterract = true;
}

void AInteractiveItem::ToggleCustomDepth(bool IsOutliningNow)
{
}

void AInteractiveItem::SetOutlineColor(int32 ColorOutline)
{
}

void AInteractiveItem::PickUpEventServer(AChel * Player)
{
}

void AInteractiveItem::PickUpEventClient(AChel * Player)
{
}
