// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "ParticleImmortal.generated.h"

UCLASS()
class MYPROJECT9_API AParticleImmortal : public AActor
{
	GENERATED_BODY()
	
public:	
	AParticleImmortal();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Particle")
		UParticleSystemComponent* PS;

};
