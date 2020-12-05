// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "GeneratorLampochka.h"

#include "GeneratorArea.generated.h"

UCLASS()
class MYPROJECT9_API AGeneratorArea : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeneratorArea();

	void DoSomethinkGen();

	UFUNCTION(NetMulticast, Reliable)
	void ChangeLampochka();

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// declare overlap end function
	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
		UBoxComponent* Collision;


	void GetLifetimeReplicatedProps(TArray < FLifetimeProperty >& OutLifetimeProps) const override;

	UPROPERTY(Replicated)
	int32 Stadiya;
	UPROPERTY(Replicated)
	bool IsAvalible;

	UPROPERTY(EditAnywhere)
	AGeneratorLampochka* Lamp;
};
