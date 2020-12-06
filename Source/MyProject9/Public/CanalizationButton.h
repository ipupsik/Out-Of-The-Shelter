// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

#include "CanalizationButton.generated.h"

UCLASS()
class MYPROJECT9_API ACanalizationButton : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACanalizationButton();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

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
		UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Button")
		UBoxComponent* Collision;

	bool DoesRefresh;
};
