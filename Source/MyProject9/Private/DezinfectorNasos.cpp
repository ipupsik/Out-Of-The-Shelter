// Fill out your copyright notice in the Description page of Project Settings.


#include "DezinfectorNasos.h"
#include "GS.h"

// Sets default values
ADezinfectorNasos::ADezinfectorNasos()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bIsAvaliable = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	Scene->SetupAttachment(RootComponent);

	Nasos = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Nasos"));
	Nasos->SetupAttachment(Scene);

	Lampochka = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lampochka"));
	Lampochka->SetupAttachment(Scene);
}

void ADezinfectorNasos::BeginPlay()
{
	if (GetLocalRole() == ROLE_Authority) {
		CurTurnOffCount = 1 + FMath::Rand() % ArrayOfZatichki.Num();
		for (int i = 0; i < CurTurnOffCount; i++)
		{
			int32 NewIndex = FMath::Rand() % ArrayOfZatichki.Num();
			while (!ArrayOfZatichki[NewIndex]->DoesLock)
			{
				NewIndex++;
				if (NewIndex == ArrayOfZatichki.Num())
					NewIndex = 0;
			}
			ArrayOfZatichki[NewIndex]->SwitchAnimUp();
		}
	}
}

void ADezinfectorNasos::TurnOn()
{
	AGS* GS = GetWorld()->GetGameState<AGS>();
	GS->CanalizaciaNasosCount--;
	if (GS->CanalizaciaNasosCount == 0)
	{
		GS->IsCanalizaciaAvaliable = true;
		GS->OffCollisionNasosi_Implementation();

	}
	TurnOnMulticast();
}

void ADezinfectorNasos::TurnOnMulticast_Implementation()
{
	TurnOnSound();
	bIsAvaliable = false;
	Lampochka->SetMaterial(0, MaterialLampochkaOn);
}