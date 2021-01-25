// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "QAbility.generated.h"

class AQAbilityItem;
class AChel;
/**
 * 
 */
UCLASS(Blueprintable)
class MYPROJECT9_API UQAbility : public UObject
{
	GENERATED_BODY()
public:
	virtual bool UseAbilityClient(AChel* Player);
	virtual void UseAbilityServer(AChel* Player);

	virtual bool DeUseAbilityClient(AChel* Player);
	virtual void DeUseAbilityServer(AChel* Player);

	virtual FVector GetCacheScale3D(int32 CacheIndex);
	virtual FRotator GetCacheRotation(int32 CacheIndex);
	virtual FVector GetCacheLocation(int32 CacheIndex);

	UPROPERTY(EditAnywhere, Category = "Main_Vars")
		TSubclassOf<AQAbilityItem> QAbilityitem_class;
	UPROPERTY(EditAnywhere)
		UObject* Icon;
};
