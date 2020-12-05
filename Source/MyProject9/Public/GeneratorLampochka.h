// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/Material.h"

#include "GeneratorLampochka.generated.h"

UCLASS()
class MYPROJECT9_API AGeneratorLampochka : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeneratorLampochka();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Lampa")
	UStaticMeshComponent* LampochkaModel;

	UPROPERTY(EditAnywhere)
	UMaterial* MaterialOff;
	UPROPERTY(EditAnywhere)
	UMaterial* MaterialOn;

};
