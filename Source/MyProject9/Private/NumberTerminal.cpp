// Fill out your copyright notice in the Description page of Project Settings.


#include "NumberTerminal.h"

// Sets default values
ANumberTerminal::ANumberTerminal()
{
	MaterialsNum.Init(0, 0);

	Decal = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal"));
	Decal->SetupAttachment(RootComponent);
}

void ANumberTerminal::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ANumberTerminal, NumberType);
}

void ANumberTerminal::BeginPlay() {
	AActor::BeginPlay();


	Decal->SetMaterial(0, MaterialsNum[NumberType]);
}