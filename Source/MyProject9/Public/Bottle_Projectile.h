// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon_Projectile.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Bottle_Projectile.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT9_API ABottle_Projectile : public AWeapon_Projectile
{
	GENERATED_BODY()
public:
	ABottle_Projectile();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UBoxComponent* MyCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* MyGunMesh;

	UFUNCTION(BlueprintImplementableEvent)
		void PlaySoundBroke();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TimeEffect;
	UFUNCTION(BlueprintCallable)
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	
};
