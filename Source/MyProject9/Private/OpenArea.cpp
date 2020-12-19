// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenArea.h"

AOpenArea::AOpenArea() {
	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	Collision->SetupAttachment(RootComponent);
	Type = 3;
	bIsAvaliable = true;
}

void AOpenArea::GetLifetimeReplicatedProps(TArray < FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AOpenArea, bIsAvaliable);
}

void AOpenArea::DoSomethink()
{

}