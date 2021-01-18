// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon_Projectile.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TakableProjectile.generated.h"

class AWeapon_Level;
/**
 * 
 */
UCLASS()
class MYPROJECT9_API ATakableProjectile : public AWeapon_Projectile
{
	GENERATED_BODY()
	
public:
	ATakableProjectile();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* MyCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* MyGunMesh;

	UFUNCTION(BlueprintImplementableEvent)
		void PlaySoundHitChel();

	UFUNCTION(BlueprintImplementableEvent)
		void PlaySoundHitNotChel();

	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);


	UPROPERTY(EditAnywhere, Category = "WeaponLevel_Class")
		TSubclassOf<AWeapon_Level> WeaponLevel_Class;
};
