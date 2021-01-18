// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ConsumableAbility.generated.h"

class AChel;
class URAbilitySlot;
/**
 * 
 */
UCLASS()
class MYPROJECT9_API UConsumableAbility : public UObject
{
	GENERATED_BODY()
	
public:
	virtual void UseAbilityClient(AChel*);
	virtual void UseAbilityServer(AChel*);

	void SetAbilityToSlot();
	void UpdateCount();
	void SetCurRAbilityUserView(AChel*);

	int32 CurCount;
	UPROPERTY(EditAnywhere)
		int32 MaxCountToStack;
	UPROPERTY(EditAnywhere)
		UObject* Icon;
	URAbilitySlot* UserViewSlot;
};
