// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenArea.h"

AOpenArea::AOpenArea() {
	Type = 3;
	bIsAvaliable = true;
	bIsUsed = false;
	CurTimeVentil = 0.0f;
}

void AOpenArea::GetLifetimeReplicatedProps(TArray < FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AOpenArea, bIsAvaliable);
	DOREPLIFETIME(AOpenArea, bIsUsed);
	DOREPLIFETIME(AOpenArea, CurTimeVentil);
}

void AOpenArea::DoSomethink()
{

}