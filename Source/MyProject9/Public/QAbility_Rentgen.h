// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QAbility.h"
#include "QAbility_Rentgen.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT9_API UQAbility_Rentgen : public UQAbility
{
	GENERATED_BODY()
	
	FVector GetCacheScale3D(int32 CacheIndex) override;
	FRotator GetCacheRotation(int32 CacheIndex) override;
	FVector GetCacheLocation(int32 CacheIndex) override;
};
