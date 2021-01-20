// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Weapon_Character.generated.h"

class AChel;
class AWeapon_Level;
class AWeapon_Projectile;
UCLASS()
class MYPROJECT9_API AWeapon_Character : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeapon_Character();

	void Throw();
	void SpawnProjectile();
	UFUNCTION(NetMulticast, Reliable)
	void DropItem();

	UFUNCTION(BlueprintImplementableEvent)
	void AnimationThrow();
	UFUNCTION(BlueprintImplementableEvent)
	void AnimationThrowReverse();


	UFUNCTION(BlueprintCallable)
	void AnimationThrow_Finished();
	UFUNCTION(BlueprintCallable)
	void AnimationThrowReverse_Finished();


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 LeftAmmo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxAmmo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator RotationProjectile;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator RotationDroppedItem;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText WeaponName;
	UPROPERTY(BlueprintReadWrite)
	AChel* WeaponOwner;

	UPROPERTY(EditAnywhere, Category = "ProjectileClass")
		TSubclassOf<AWeapon_Projectile> WeaponProjectileClass;
	UPROPERTY(EditAnywhere, Category = "Weapon_LevelClass")
		TSubclassOf<AWeapon_Level> WeaponLevelClass;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* GunMesh;
};
