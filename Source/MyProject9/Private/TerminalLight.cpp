// Fill out your copyright notice in the Description page of Project Settings.


#include "TerminalLight.h"

// Sets default values
ATerminalLight::ATerminalLight()
{
	Lamp = CreateDefaultSubobject<UStaticMeshComponent>("Lampa");
	Lamp->SetupAttachment(RootComponent);

	MaterialOn = CreateDefaultSubobject<UMaterial>(TEXT("MaterialOn"));
	MaterialOff = CreateDefaultSubobject<UMaterial>(TEXT("MaterialOff"));
	MaterialDefault = CreateDefaultSubobject<UMaterial>(TEXT("MaterialDefault"));

	Lamp->SetMaterial(0, MaterialDefault);
}

void ATerminalLight::ChangeMaterialLamp_Implementation(int32 CodeColor)
{
	switch (CodeColor)
	{
	case 0:
	{
		Lamp->SetMaterial(0, MaterialDefault);
		break;
	}
	case 1:
	{
		Lamp->SetMaterial(0, MaterialOff);
		break;
	}
	case 2:
	{
		Lamp->SetMaterial(0, MaterialOn);
		break;
	}
	}
}
