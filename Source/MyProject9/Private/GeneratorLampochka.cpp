// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneratorLampochka.h"

// Sets default values
AGeneratorLampochka::AGeneratorLampochka()
{
	LampochkaModel = CreateDefaultSubobject<UStaticMeshComponent>("Lampa");
	LampochkaModel->SetupAttachment(RootComponent);

	MaterialOn = CreateDefaultSubobject<UMaterial>(TEXT("MaterialOn"));
	MaterialOff = CreateDefaultSubobject<UMaterial>(TEXT("MaterialOff"));

	LampochkaModel->SetMaterial(0, MaterialOff);
}