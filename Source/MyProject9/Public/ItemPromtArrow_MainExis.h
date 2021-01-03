// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemPromtArrow.h"
#include "ItemPromtArrow_MainExis.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT9_API AItemPromtArrow_MainExis : public AItemPromtArrow
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		int32 Type;
};
