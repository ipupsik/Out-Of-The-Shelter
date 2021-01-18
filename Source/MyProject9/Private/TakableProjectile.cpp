// Fill out your copyright notice in the Description page of Project Settings.


#include "TakableProjectile.h"
#include "Weapon_Level.h"
#include "Chel.h"

ATakableProjectile::ATakableProjectile() {
	MyCollision = CreateDefaultSubobject<UBoxComponent>("MyCollision");
	MyCollision->SetupAttachment(RootComponent);

	MyGunMesh = CreateDefaultSubobject<UStaticMeshComponent>("MyGunMesh");
	MyGunMesh->SetupAttachment(MyCollision);

	ProjectMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));

	MyCollision->OnComponentBeginOverlap.AddDynamic(this, &ATakableProjectile::OnOverlapBegin);
	MyCollision->OnComponentHit.AddDynamic(this, &ATakableProjectile::OnHit);

}

void ATakableProjectile::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	AChel* Player = nullptr;
	Player = Cast<AChel>(OtherActor);
	if (Player) {
		if (Player->Index != IndexOwner) {
			if (GetLocalRole() == ROLE_Authority) {
				Player->Health -= Damage;
			}
			PlaySoundHitChel();
			Destroy();
		}
	}
}

void ATakableProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	AChel* Player = nullptr;
	Player = Cast<AChel>(OtherActor);
	if (!Player) {
		PlaySoundHitNotChel();
		if (GetLocalRole() == ROLE_Authority) {
			AWeapon_Level* CreatedWeaponLevel = GetWorld()->SpawnActor<AWeapon_Level>(WeaponLevel_Class, GetTransform());
			CreatedWeaponLevel->Collision->SetPhysicsLinearVelocity(GetVelocity() / 2);
		}
		Destroy();
	}
}