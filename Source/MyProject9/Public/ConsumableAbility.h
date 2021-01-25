// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Sound/SoundWave.h"
#include "ConsumableAbility.generated.h"

class AChel;
class URAbilitySlot;
/**
 * 
 */
UCLASS(Blueprintable)
class MYPROJECT9_API UConsumableAbility : public UObject
{
	GENERATED_BODY()
	
public:
	virtual bool UseAbilityClient(AChel* Player);
	virtual void UseAbilityServer(AChel* Player);

	UPROPERTY(EditAnywhere)
		USoundWave* MySoundWave;

	void SetAbilityToSlot();
	void UpdateCount();
	void SetCurRAbilityUserView(AChel* Player);
	UFUNCTION(BlueprintCallable)
		void ResetAbility();
	UFUNCTION(BlueprintCallable)
		void ResetCurRAbilityUserView(AChel* Player);

	int32 CurCount;
	UPROPERTY(EditAnywhere)
		int32 MaxCountToStack;
	UPROPERTY(EditAnywhere)
		UObject* Icon;
	UPROPERTY(BlueprintReadWrite)
		URAbilitySlot* UserViewSlot;
	UPROPERTY(EditAnywhere)
		float Duration;
};
