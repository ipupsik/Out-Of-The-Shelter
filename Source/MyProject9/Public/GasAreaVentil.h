// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OpenArea.h"
#include "DamageAreaCPP.h"
#include "ParticleGasCPP.h"
#include "GasAreaVentil.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT9_API AGasAreaVentil : public AOpenArea
{
	GENERATED_BODY()
public:
	AGasAreaVentil();
	void DoSomethink() override;
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
