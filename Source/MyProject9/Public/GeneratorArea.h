// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "GeneratorLampochka.h"
#include "AreaCollision.h"

#include "GeneratorArea.generated.h"

class APromptCollisionArea;
class AChel;

UCLASS()
class MYPROJECT9_API AGeneratorArea : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeneratorArea();

	void DoSomethinkGen();

	UFUNCTION(BlueprintImplementableEvent)
		void ChangeSoundAmbientToWorking();
	UFUNCTION(BlueprintImplementableEvent)
		void ChangeSoundAmbientToNotWorking();

	UFUNCTION(NetMulticast, Reliable)
	void ChangeLampochka(int32 type);

	void PressedEGenerator(AChel* Player);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText PromptGenNotRepairing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText PromptGenTextRepairing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText PromptGenTextNotActive;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// declare overlap end function
	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
		UBoxComponent* Collision;

	UPROPERTY(EditAnywhere)
		TArray<APromptCollisionArea*> PromtCollisionGenerator;

	UPROPERTY(EditAnywhere)
		TArray<APromptCollisionArea*> PromtCollisionTerminal;

	UPROPERTY(EditAnywhere)
		TArray <AAreaCollision*> ShelterCollision;

	void GetLifetimeReplicatedProps(TArray < FLifetimeProperty >& OutLifetimeProps) const override;

	void RefreshGenerator();

	UPROPERTY(Replicated)
	int32 Stadiya;
	UPROPERTY(Replicated)
	bool IsAvalible;

	UPROPERTY(EditAnywhere)
	AGeneratorLampochka* Lamp;
};
