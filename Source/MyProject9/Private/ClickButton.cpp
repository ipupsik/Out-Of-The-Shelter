// Fill out your copyright notice in the Description page of Project Settings.


#include "ClickButton.h"

AClickButton::AClickButton()
{
	Decal = CreateDefaultSubobject<UDecalComponent>("Decal");
	Decal->SetupAttachment(Collision);
}

void AClickButton::BeginPlay()
{
	APickableItem::BeginPlay();

	Decal->SetMaterial(0, MaterialsNum[ButtonType]);
}