// Fill out your copyright notice in the Description page of Project Settings.


#include "TerminalNumber.h"
#include "Net/UnrealNetwork.h"

ATerminalNumber::ATerminalNumber()
{
	Decal = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal"));
	Decal->SetupAttachment(RootComponent);
}

void ATerminalNumber::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(ATerminalNumber, NumberType, COND_InitialOnly);
}

void ATerminalNumber::BeginPlay()
{
	Super::BeginPlay();
	if (GetLocalRole() == ROLE_Authority)
	{
		Decal->SetMaterial(0, MaterialsNum[NumberType]);
	}
}

void ATerminalNumber::OnRep_DecalInitial()
{
	Decal->SetMaterial(0, MaterialsNum[NumberType]);
}