// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OpenAreaCPP.h"
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
	
	UPROPERTY(EditAnywhere)
	FName GasAreaDamageTag;
	UPROPERTY(EditAnywhere)
	FName GasAreaPointTag;
	UPROPERTY(EditAnywhere)
		int32 CurrentAreaType;

	//UPROPERTY(EditAnywhere)
		//TSubclassOf<>
};
