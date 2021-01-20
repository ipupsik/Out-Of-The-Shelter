// Fill out your copyright notice in the Description page of Project Settings.


#include "Stone_Projectile.h"
#include "Chel.h"

AStone_Projectile::AStone_Projectile() {
	LastTimeHited = 0.f;
	LastHitedActor = nullptr;

	MyGunMesh = CreateDefaultSubobject<UStaticMeshComponent>("MyGunMesh");
	MyGunMesh->SetupAttachment(RootComponent);

	MyCollision = CreateDefaultSubobject<USphereComponent>("MyCollision");
	MyCollision->SetupAttachment(MyGunMesh);

	ProjectMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectMovement->SetUpdatedComponent(MyGunMesh);

	MyCollision->OnComponentBeginOverlap.AddDynamic(this, &AStone_Projectile::OnOverlapBegin);
	MyGunMesh->OnComponentHit.AddDynamic(this, &AStone_Projectile::OnHit);
}

void AStone_Projectile::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	AChel* Player = nullptr;
	Player = Cast<AChel>(OtherActor);
	if (Player) {
		if (Player->Index != IndexOwner) {
			if (Player->DamageCollision == OtherComp) {
				if (Player->GetLocalRole() == ROLE_Authority) {
					Player->Health -= Damage;
				}
				PlaySoundHitChel();
				Destroy();
			}
		}
	}
}

void AStone_Projectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, 
	FVector NormalImpulse, const FHitResult& Hit) {
	AChel* Player = nullptr;
	Player = Cast<AChel>(OtherActor);
	if (!Player && OtherActor) {
		if (OtherActor == LastHitedActor) {
			if (GetGameTimeSinceCreation() - LastTimeHited > 0.7f) {
				LastTimeHited = GetGameTimeSinceCreation();
				PlaySoundHitNotChel();
			}
		}
		else {
			LastHitedActor = OtherActor;
			LastTimeHited = GetGameTimeSinceCreation();
			PlaySoundHitNotChel();
		}
	}
}