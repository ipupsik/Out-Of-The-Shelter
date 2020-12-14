// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/Material.h"

#include "TerminalLight.generated.h"

UCLASS()
class MYPROJECT9_API ATerminalLight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATerminalLight();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Lampa")
	UStaticMeshComponent* Lamp;

	UPROPERTY(EditAnywhere)
		UMaterial* MaterialOff;
	UPROPERTY(EditAnywhere)
		UMaterial* MaterialOn;
	UPROPERTY(EditAnywhere)
		UMaterial* MaterialDefault;

	UFUNCTION(NetMulticast, Reliable)
		void ChangeMaterialLamp(int32 CodeColor);
};
