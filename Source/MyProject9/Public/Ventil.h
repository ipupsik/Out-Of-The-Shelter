// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveItem.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/TargetPoint.h"
#include "Ventil.generated.h"

/**
 * 
 */
class AParticleGasCPP;
class ADamageAreaCPP;
UCLASS()
class MYPROJECT9_API AVentil : public AInteractiveItem
{
	GENERATED_BODY()
public:
	AVentil();

	void PickUpEventServer(AChel* Player) override;
	bool PickUpEventClient(AChel* Player) override;
	void OnLineTraced(AChel* Player) override;
	void ToggleCustomDepth(bool NewIsOutliningNow, AChel* Player) override;
	void SetOutlineColor(int32 ColorOutline) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Collision")
		UBoxComponent* Collision;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Scene")
		USceneComponent* Scene;

	UFUNCTION(BlueprintImplementableEvent)
		void PlaySoundGas(FVector Location);

	void GetLifetimeReplicatedProps(TArray < FLifetimeProperty >& OutLifetimeProps) const override;

	UPROPERTY(EditAnywhere)
		FName GasAreaDamageTag;
	UPROPERTY(EditAnywhere)
		FName GasAreaParticleTag;

	UPROPERTY(EditAnywhere)
		TSubclassOf<ADamageAreaCPP> DamageAreaClass;

	UFUNCTION(Server, Reliable, WithValidation)
		void CallReverseAnimation();

	UPROPERTY(EditAnywhere)
		TSubclassOf<AParticleGasCPP> PS_Class;

	UPROPERTY(EditAnywhere)
		FText AreaUsedText;

	void DeleteAllObjects();
	
	UFUNCTION(NetMulticast, Reliable)
		void ChangeCanInterract(bool val);
	UFUNCTION(NetMulticast, Reliable)
		void ChangeIndexOwner(int32 idx);

	UFUNCTION(BlueprintImplementableEvent)
		void RotateVentil();
	UFUNCTION(BlueprintImplementableEvent)
		void RotateVentilReverse();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
		float TimeVentilAnim;

	void CreateGasOnLevel();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 areaType;

	int32 IndexOwner;

	bool PickUpEventReleaseClient(AChel* Player) override;
	void PickUpEventReleaseServer(AChel* Player) override;
};
