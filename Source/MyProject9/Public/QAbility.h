// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "QAbility.generated.h"

class AQAbilityItem;
/**
 * 
 */
UCLASS()
class MYPROJECT9_API UQAbility : public UObject
{
	GENERATED_BODY()
public:
	virtual FVector GetCacheScale3D();
	virtual FRotator GetCacheRotation();
	virtual FVector GetCacheLocation();

	UPROPERTY(EditAnywhere, Category = "Main_Vars")
		TSubclassOf<AQAbilityItem> QAbilityitem_class;
};
