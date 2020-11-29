// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"

#include "WebCamSpectator.generated.h"

UCLASS()
class MYPROJECT9_API AWebCamSpectator : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AWebCamSpectator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
		UCameraComponent* CameraComp;

	UPROPERTY(BlueprintReadOnly)
		int32 Index;
};
