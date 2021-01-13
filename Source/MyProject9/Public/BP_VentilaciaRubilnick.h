// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickableItem.h"
#include "BP_VentilaciaRubilnick.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT9_API ABP_VentilaciaRubilnick : public APickableItem
{
	GENERATED_BODY()
	
public:
	ABP_VentilaciaRubilnick();

	UFUNCTION(BlueprintImplementableEvent)
		void Open();

	void CheckVentilaciaAvaliable();

	UFUNCTION(NetMulticast, Reliable)
		void ChangeAvaliable();

	bool is_Avaliable;
};
