// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QAbility.h"
#include "QAbility_ChelDetector.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT9_API UQAbility_ChelDetector : public UQAbility
{
	GENERATED_BODY()
public:

	virtual bool UseAbilityClient(AChel* Player) override;
	void DeUseAbilityClient();

	FVector GetCacheScale3D(int32 CacheIndex) override;
	FRotator GetCacheRotation(int32 CacheIndex) override;
	FVector GetCacheLocation(int32 CacheIndex) override;
};
