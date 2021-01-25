// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "DamageAreaCPP.generated.h"

UCLASS()
class MYPROJECT9_API ADamageAreaCPP : public AActor
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
public:	
	// Sets default values for this actor's properties
	ADamageAreaCPP();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
	UBoxComponent* Collision;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	int32 areaType;

};
