// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemPromtArrow.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "ButtonCanalization.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT9_API AButtonCanalization : public AItemPromtArrow
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	AButtonCanalization();

protected:

public:
	UFUNCTION(NetMulticast, Reliable)
		void DisableCollision();

	UFUNCTION(NetMulticast, Reliable)
		void EnableCollision();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void ForwardAnimation();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void ReverceAnimation();

	void Open();
	void Close();
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Button")
		UBoxComponent* Collision;

	bool DoesRefresh;
};
