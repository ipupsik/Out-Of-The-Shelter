// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h"
#include "ItemPromtArrow.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Chel.h"

#include "PromptCollisionArea.generated.h"

UCLASS()
class MYPROJECT9_API APromptCollisionArea : public AActor
{
	GENERATED_BODY()
	
public:	

	void GetLifetimeReplicatedProps(TArray < FLifetimeProperty >& OutLifetimeProps) const override;

	// Sets default values for this actor's properties
	APromptCollisionArea();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<AItemPromtArrow*> PromptedItems;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
		UBoxComponent* Collision;

	UPROPERTY(Replicated)
		bool bISAvaliable;
	
	UPROPERTY(EditAnywhere)
		int32 TypePromptCollision;

};
