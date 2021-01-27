// Fill out your copyright notice in the Description page of Project Settings.


#include "ParticleGasRandomEvent.h"

// Sets default values
AParticleGasRandomEvent::AParticleGasRandomEvent()
{
	PS = CreateDefaultSubobject<UParticleSystemComponent>("ParticleSystem");
	PS->SetupAttachment(RootComponent);
}

