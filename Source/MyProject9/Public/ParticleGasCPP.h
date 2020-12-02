// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "ParticleGasCPP.generated.h"

UCLASS()
class MYPROJECT9_API AParticleGasCPP : public AActor
{
	GENERATED_BODY()
	
public:	
	AParticleGasCPP();
	
	UParticleSystemComponent* PS;
	int32 areaType;
};
