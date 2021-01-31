// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GS.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/SphereComponent.h"

#include "Spectator.generated.h"

class AChel;

UCLASS()
class MYPROJECT9_API ASpectator : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASpectator();

	UPROPERTY(EditAnywhere, Category = "UI HUD")
		TSubclassOf<UUserWidget> SpectatorWidget_class;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;

public:	

	UFUNCTION(BlueprintImplementableEvent)
		void CameraSwitch();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void LookUp(float);
	void LookRight(float);
	void ChangeSpecRight();
	void ChangeSpecLeft();
	void GoRight(float);
	void GoForward(float);
	UFUNCTION(Server, Reliable, WithValidation)
		void UpdateSpectating_Left();
	UFUNCTION(Server, Reliable, WithValidation)
		void UpdateSpectating_Right();
	UFUNCTION(Server, Reliable, WithValidation)
		void TargetArmFreeCamera();
	UFUNCTION(NetMulticast, Reliable)
		void TargetArmNotFreeCamera_Multicast();
	UFUNCTION(Server, Reliable, WithValidation)
		void TargetArmNotFreeCamera_Server();

	void GoToFreeCamera();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void GetLifetimeReplicatedProps(TArray < FLifetimeProperty >& OutLifetimeProps) const override;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
		UCameraComponent* CameraComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SpringArm")
		USpringArmComponent* SpringArm;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Collision")
		//USphereComponent* Collision;

	UPROPERTY(Replicated, BlueprintReadOnly)
		AChel* Player;
	int32 Index;
	int32 Layer;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float Sensetivity;
	UPROPERTY(Replicated, BlueprintReadOnly)
	bool IsKilled;

	UPROPERTY(Replicated, BlueprintReadOnly)
		bool IsFreeCam;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
		UFloatingPawnMovement* PawnMovement;

	AGS* GS;
};
