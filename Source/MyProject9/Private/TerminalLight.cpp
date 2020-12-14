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