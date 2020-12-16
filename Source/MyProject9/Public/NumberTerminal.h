// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/DecalComponent.h"
#include "Net/UnrealNetwork.h"
#include "Materials/Material.h"

#include "NumberTerminal.generated.h"

UCLASS()
class MYPROJECT9_API ANumberTerminal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANumberTerminal();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	UPROPERTY(Replicated)
		int32 NumberType;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Govno(Bagannoe)")
	UDecalComponent* Decal;
	
	UPROPERTY(EditAnywhere)
		TArray<UMaterial*> MaterialsNum;

protected:
	virtual void BeginPlay() override;

};
