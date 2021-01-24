// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/DecalComponent.h"
#include "Materials/Material.h"
#include "TerminalNumber.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT9_API ATerminalNumber : public AActor
{
	GENERATED_BODY()
	
public:
	ATerminalNumber();

	void GetLifetimeReplicatedProps(TArray < FLifetimeProperty >& OutLifetimeProps) const override;

	void BeginPlay() override;

	UFUNCTION()
		void OnRep_DecalInitial();
	UPROPERTY(ReplicatedUsing = OnRep_DecalInitial)
		int32 NumberType;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Govno(Bagannoe)")
		UDecalComponent* Decal;

	UPROPERTY(EditAnywhere)
		TArray<UMaterial*> MaterialsNum;
};
