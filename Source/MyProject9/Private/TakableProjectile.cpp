// Fill out your copyright notice in the Description page of Project Settings.


#include "TakableProjectile.h"
#include "Weapon_Level.h"
#include "Chel.h"

ATakableProjectile::ATakableProjectile() {
	MyCollision = CreateDefaultSubobject<UBoxComponent>("MyCollision");
	RootComponent = MyCollision;

	MyGunMesh = CreateDefaultSubobject<UStaticMeshComponent>("MyGunMesh");
	MyGunMesh->SetupAttachment(MyCollision);

	ProjectMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));

	MyCollision->OnComponentBeginOverlap.AddDynamic(this, &ATakableProjectile::OnOverlapBegin);
	MyGunMesh->OnComponentHit.AddDynamic(this, &ATakableProjectile::OnHit);

}

void ATakableProjectile::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	AChel* Player = nullptr;
	Player = Cast<AChel>(OtherActor);
	if (Player) {
		if (Player->Index != IndexOwner) {
			UE_LOG(LogTemp, Warning, TEXT("Weapon hit chel"));
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
			UE_LOG(LogTemp, Warning, TEXT("WeaponWasSpawned"));
			SpawnWeapLevel();
			/*FTransform transfrm;
			transfrm.SetLocation(GetActorLocation());
			transfrm.SetRotation(FQuat(GetActorRotation()));
			transfrm.SetScale3D({ 1.0f, 1.0f, 1.0f });
			FActorSpawnParameters SpwnParam;
			AWeapon_Level* CreatedWeaponLevel = GetWorld()->SpawnActor<AWeapon_Level>(WeaponLevel_Class, transfrm, SpwnParam);
			//CreatedWeaponLevel->Collision->SetPhysicsLinearVelocity(GetVelocity() / 2);*/
		}
		Destroy();
	}
}