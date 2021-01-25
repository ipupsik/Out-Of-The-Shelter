// Fill out your copyright notice in the Description page of Project Settings.


#include "TakableProjectile.h"
#include "Weapon_Level.h"
#include "Chel.h"

ATakableProjectile::ATakableProjectile() {
	MyGunMesh = CreateDefaultSubobject<UStaticMeshComponent>("MyGunMesh");
	MyGunMesh->SetupAttachment(RootComponent);

	MyCollision = CreateDefaultSubobject<UBoxComponent>("MyCollision");
	MyCollision->SetupAttachment(MyGunMesh);

	ProjectMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectMovement->SetUpdatedComponent(MyGunMesh);

	MyCollision->OnComponentBeginOverlap.AddDynamic(this, &ATakableProjectile::OnOverlapBegin);
	MyGunMesh->OnComponentHit.AddDynamic(this, &ATakableProjectile::OnHit);
}

void ATakableProjectile::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	AChel* Player = nullptr;
	Player = Cast<AChel>(OtherActor);
	if (Player) {
		if (Player->Index != IndexOwner) {
			if (Player->DamageCollision == OtherComp) {
				if (Player->IsInGame)
				{
					UE_LOG(LogTemp, Warning, TEXT("Weapon hit chel"));
					if (Player->GetLocalRole() == ROLE_Authority) {
						Player->Health += GetDamage(Player);
						if (Player->Health + DeltaRadiation >= 1.0f)
						{
							Player->KillerIndex = IndexOwner;
						}

						if (Player->Health >= 1.0f)
						{

							TArray<AActor*>Players;
							UGameplayStatics::GetAllActorsOfClass(Player->World, Player->GetClass(), Players);
							for (auto& it : Players)
								Cast<AChel>(it)->RefreshWidgets(Player->DoesHave, Player->KillerIndex, Player->Index);
							Player->DoesHave.Init(false, 3);
							Player->bCanWalkingAndWatching = true;
							Player->KillPlayer();
						}
						CallAddMarker();
					}
				}
				PlaySoundHitChel();
				Destroy();
			}
		}
	}
}

void ATakableProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	AChel* Player = nullptr;
	Player = Cast<AChel>(OtherActor);
	if (!Player) {
		if (OtherActor) {
			PlaySoundHitNotChel();
			if (OtherActor->GetLocalRole() == ROLE_Authority) {
				UE_LOG(LogTemp, Warning, TEXT("WeaponWasSpawned"));
				FTransform transfrm;
				transfrm.SetLocation(GetActorLocation());
				transfrm.SetRotation(FQuat(GetActorRotation()));
				transfrm.SetScale3D({ 1.0f, 1.0f, 1.0f });
				FActorSpawnParameters SpwnParam;
				AWeapon_Level* CreatedWeaponLevel = GetWorld()->SpawnActor<AWeapon_Level>(WeaponLevel_Class, transfrm, SpwnParam);
				CreatedWeaponLevel->Mesh->SetPhysicsLinearVelocity(GetVelocity() / 5);
			}
			Destroy();
		}
	}
}