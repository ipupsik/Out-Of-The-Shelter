// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Weapon_Projectile.generated.h"

UCLASS()
class MYPROJECT9_API AWeapon_Projectile : public AActor
{
	GENERATED_BODY()
	
public:

	AWeapon_Projectile();

	int32 IndexOwner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UProjectileMovementComponent* ProjectMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Damage;
};
