// Fill out your copyright notice in the Description page of Project Settings.


#include "TerminalNumber.h"

ATerminalNumber::ATerminalNumber()
{
	Decal = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal"));
	Decal->SetupAttachment(RootComponent);
}

void ATerminalNumber::BeginPlay()
{
	AActor::BeginPlay();
	Decal->SetMaterial(0, MaterialsNum[NumberType]);
}
