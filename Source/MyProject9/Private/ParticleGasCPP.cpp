// Fill out your copyright notice in the Description page of Project Settings.


#include "ParticleGasCPP.h"

// Sets default values
AParticleGasCPP::AParticleGasCPP()
{
 	
	PS = CreateDefaultSubobject<UParticleSystemComponent>("ParticleSystem");
	PS->SetupAttachment(RootComponent);

}
