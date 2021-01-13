// Fill out your copyright notice in the Description page of Project Settings.


#include "VentilaciaGenerator.h"

// Sets default values
AVentilaciaGenerator::AVentilaciaGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DeltaRot = 1;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	Scene->SetupAttachment(RootComponent);

	GeneratorRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GeneratorRight"));
	GeneratorRight->SetupAttachment(Scene);

	GeneratorLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GeneratorLeft"));
	GeneratorLeft->SetupAttachment(Scene);

	PS = CreateDefaultSubobject<UParticleSystemComponent>("ParticleSystem");
	PS->SetupAttachment(Scene);
}

// Called every frame
void AVentilaciaGenerator::Tick(float DeltaTime)
{
	AActor::Tick(DeltaTime);
	if (DeltaRot == 0)
	{
		PrimaryActorTick.bCanEverTick = false;
	}
	else
	{
		GeneratorLeft->AddLocalRotation({ DeltaRot, 0.0f, 0.0f });
		GeneratorRight->AddLocalRotation({ DeltaRot, 0.0f, 0.0f });
	}
}