// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "PromptCollisionArea.h"

#include "CanalizationDamageCollision.generated.h"

UCLASS()
class MYPROJECT9_API ACanalizationDamageCollision : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACanalizationDamageCollision();
public:	
	void StopRadiation();
	void RefreshRadiation();

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// declare overlap end function
	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Area")
		UBoxComponent* Collision;

	UPROPERTY(EditAnywhere)
		float RadiationDamageCoef;
};
