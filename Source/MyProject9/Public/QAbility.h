// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "QAbility.generated.h"

class AQAbilityItem;
/**
 * 
 */
UCLASS(Blueprintable)
class MYPROJECT9_API UQAbility : public UObject
{
	GENERATED_BODY()
public:
	virtual FVector GetCacheScale3D(int32 CacheIndex);
	virtual FRotator GetCacheRotation(int32 CacheIndex);
	virtual FVector GetCacheLocation(int32 CacheIndex);

	UPROPERTY(EditAnywhere, Category = "Main_Vars")
		TSubclassOf<AQAbilityItem> QAbilityitem_class;
	UPROPERTY(EditAnywhere)
		UObject* Icon;
};
