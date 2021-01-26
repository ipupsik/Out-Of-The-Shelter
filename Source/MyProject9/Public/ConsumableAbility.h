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

	virtual FVector GetCacheScale3D(int32 CacheIndex);
	virtual FRotator GetCacheRotation(int32 CacheIndex);
	virtual FVector GetCacheLocation(int32 CacheIndex);

	UPROPERTY(EditAnywhere)
		USoundWave* MySoundWave;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText PromtText;

	void SetAbilityToSlot();

	void SetCurRAbilityUserView(AChel* Player);
	UFUNCTION(BlueprintCallable)
		void ResetAbility();
	UFUNCTION(BlueprintCallable)
		void ResetCurRAbilityUserView(AChel* Player);

	UPROPERTY(EditAnywhere)
		UObject* Icon;
	UPROPERTY(BlueprintReadWrite)
		URAbilitySlot* UserViewSlot;
	UPROPERTY(EditAnywhere)
		float Duration;

	UPROPERTY(EditAnywhere, Category = "Main_Vars")
		TSubclassOf<class AConsumable> Consumable_class;
};
