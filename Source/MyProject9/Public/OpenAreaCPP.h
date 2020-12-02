// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"

#include "OpenAreaCPP.generated.h"
UCLASS()
class MYPROJECT9_API AOpenAreaCPP : public AActor
{
	GENERATED_BODY()

public:	
	//functions
	AOpenAreaCPP();
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void ComponentOverlapEnd(UPrimitiveComponent* OverlappedComponent,  AActor* OverlappedActor,  UPrimitiveComponent* OtherActor, int32 OtherBodyIndex);
	virtual void DoSomethink();
	void GetLifetimeReplicatedProps(TArray < FLifetimeProperty >& OutLifetimeProps) const override;
	//variables
	UPROPERTY(EditAnywhere)
		int32 areaType;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
		UBoxComponent* Collision;
	UPROPERTY(Replicated)
		bool bIsAvaliable;
};
