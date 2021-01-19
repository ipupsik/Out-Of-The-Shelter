// Fill out your copyright notice in the Description page of Project Settings.


#include "Bottle_Projectile.h"
#include "Chel.h"

ABottle_Projectile::ABottle_Projectile() {
	MyGunMesh = CreateDefaultSubobject<UStaticMeshComponent>("MyGunMesh");
	MyGunMesh->SetupAttachment(RootComponent);

	MyCollision = CreateDefaultSubobject<UBoxComponent>("MyCollision");
	MyCollision->SetupAttachment(MyGunMesh);

	ProjectMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectMovement->SetUpdatedComponent(MyCollision);

	MyCollision->OnComponentBeginOverlap.AddDynamic(this, &ABottle_Projectile::OnOverlapBegin);
	MyGunMesh->OnComponentHit.AddDynamic(this, &ABottle_Projectile::OnHit);
}

void ABottle_Projectile::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	AChel* Player = nullptr;
	Player = Cast<AChel>(OtherActor);
	if (Player) {
		if (Player->Index != IndexOwner) {
			if (GetLocalRole() == ROLE_Authority) {
				Player->Health -= Damage;
			}
			if (Player->IsPlayerOwner) {
				Player->InvertMovement(TimeEffect);
			}
			PlaySoundBroke();
			Destroy();
		}
	}
}

void ABottle_Projectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	AChel* Player = nullptr;
	Player = Cast<AChel>(OtherActor);
	if (!Player) {
		PlaySoundBroke();
		Destroy();
	}
}