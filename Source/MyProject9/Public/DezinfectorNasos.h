// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Materials/Material.h"
#include "Components/StaticMeshComponent.h"
#include "DezinfectorNasosZatichka.h"
#include "DezinfectorNasos.generated.h"

UCLASS()
class MYPROJECT9_API ADezinfectorNasos : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADezinfectorNasos();

	virtual void BeginPlay() override;
	void TurnOn();
	UFUNCTION(NetMulticast, Reliable)
		void TurnOnMulticast();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
		UStaticMeshComponent* Nasos;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
		UStaticMeshComponent* Lampochka;

	UPROPERTY(VisibleAnywhere)
		UMaterial* MaterialLampochkaOn;

	UPROPERTY(EditAnywhere)
		TArray<ADezinfectorNasosZatichka*>ArrayOfZatichki;

	int32 CurTurnOffCount;
	bool bIsAvaliable;
};
