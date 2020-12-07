// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WebCamPoint.generated.h"

UCLASS()
class MYPROJECT9_API AWebCamPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWebCamPoint();

public:
	bool is_Enabled;
	UPROPERTY(EditAnywhere)
		int Index;
};
