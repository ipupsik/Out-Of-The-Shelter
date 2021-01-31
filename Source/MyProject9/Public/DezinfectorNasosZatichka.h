// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveItem.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Components/SceneComponent.h"
#include "DezinfectorNasosZatichka.generated.h"

class ADezinfectorNasos;

UCLASS()
class MYPROJECT9_API ADezinfectorNasosZatichka : public AInteractiveItem
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADezinfectorNasosZatichka();

	void Interact();

	UFUNCTION(BlueprintImplementableEvent)
		void SwitchAnimUp();
	UFUNCTION(BlueprintImplementableEvent)
		void SwitchAnimDown();

	void PickUpEventServer(AChel* Player) override;
	bool PickUpEventClient(AChel* Player) override;
	void OnLineTraced(AChel* Player) override;
	void ToggleCustomDepth(bool NewIsOutliningNow, AChel* Player) override;
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle")
		UParticleSystemComponent* PS;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
		USceneComponent* Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
		UStaticMeshComponent* Zatichka;

	UPROPERTY(EditAnywhere)
		ADezinfectorNasos* Nasos;
	UPROPERTY(BlueprintReadWrite)
		bool DoesLock;
	UPROPERTY(BlueprintReadWrite)
		bool DoesPlayAnim;

	UPROPERTY(EditAnywhere)
		FSlateColor MyColor;
};
