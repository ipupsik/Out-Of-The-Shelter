// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickableItem.h"
#include "Components/DecalComponent.h"
#include "Materials/Material.h"
#include "Components/BoxComponent.h"
#include "ClickButton.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT9_API AClickButton : public APickableItem
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

public:
	AClickButton();

	UPROPERTY(EditAnyWhere)
		int32 ButtonType;

	UPROPERTY(EditAnywhere)
		TArray<UMaterial*> MaterialsNum;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
		UDecalComponent* Decal;
};
