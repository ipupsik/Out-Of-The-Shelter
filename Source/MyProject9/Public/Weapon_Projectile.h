// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon_Projectile.generated.h"

class AChel;

UCLASS()
class MYPROJECT9_API AWeapon_Projectile : public AActor
{
	GENERATED_BODY()
	
public:

	AWeapon_Projectile();

	int32 IndexOwner;

	float GetDamage(AChel* Player);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UProjectileMovementComponent* ProjectMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Damage;

	void CallAddMarker();
};
