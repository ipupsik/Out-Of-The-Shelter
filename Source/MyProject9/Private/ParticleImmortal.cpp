// Fill out your copyright notice in the Description page of Project Settings.


#include "ParticleImmortal.h"

// Sets default values
AParticleImmortal::AParticleImmortal()
{
	PS = CreateDefaultSubobject<UParticleSystemComponent>("ParticleSystem");
	PS->SetupAttachment(RootComponent);
}

