// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon_Projectile.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Stone_Projectile.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT9_API AStone_Projectile : public AWeapon_Projectile
{
	GENERATED_BODY()
public:
	AStone_Projectile();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		USphereComponent* MyCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* MyGunMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LastTimeHited;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor* LastHitedActor;


	UFUNCTION(BlueprintImplementableEvent)
		void PlaySoundHitChel();

	UFUNCTION(BlueprintImplementableEvent)
		void PlaySoundHitNotChel();
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);


};
