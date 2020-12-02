// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OpenAreaCPP.h"
#include "DamageAreaCPP.h"
#include "ParticleGasCPP.h"

#include "GasArea.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT9_API AGasArea : public AOpenAreaCPP
{
	GENERATED_BODY()
public:
	AGasArea();
	void DoSomethink() override;
public:
	UPROPERTY(EditAnywhere)
	FName GasAreaDamageTag;
	UPROPERTY(EditAnywhere)
	FName GasAreaParticleTag;
	UPROPERTY(EditAnywhere)
		int32 CurrentAreaType;

	UPROPERTY(EditAnywhere)
		TSubclassOf<ADamageAreaCPP> DamageAreaClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AParticleGasCPP> PS_Class;

	void DeleteAllObjects();
};
