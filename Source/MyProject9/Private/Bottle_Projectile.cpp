// Fill out your copyright notice in the Description page of Project Settings.


#include "Bottle_Projectile.h"
#include "Chel.h"

ABottle_Projectile::ABottle_Projectile() {
	MyGunMesh = CreateDefaultSubobject<UStaticMeshComponent>("MyGunMesh");
	MyGunMesh->SetupAttachment(RootComponent);

	MyCollision = CreateDefaultSubobject<UBoxComponent>("MyCollision");
	MyCollision->SetupAttachment(MyGunMesh);

	ProjectMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectMovement->SetUpdatedComponent(MyGunMesh);

	MyCollision->OnComponentBeginOverlap.AddDynamic(this, &ABottle_Projectile::OnOverlapBegin);
	MyGunMesh->OnComponentHit.AddDynamic(this, &ABottle_Projectile::OnHit);
}

void ABottle_Projectile::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	AChel* Player = nullptr;
	Player = Cast<AChel>(OtherActor);
	if (Player) {
		if (Player->Index != IndexOwner) {
			if(Player->DamageCollision == OtherComp){
				if (Player->IsInGame)
				{
					UE_LOG(LogTemp, Warning, TEXT("Weapon hit chel"));
					if (Player->GetLocalRole() == ROLE_Authority) {
						Player->Health += Damage / (1 + 0.2 * Player->ShieldsCount) * Player->DoesNotImmortal;
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
					}
				}
				if (Player->IsPlayerOwner) {
					Player->InvertMovement(TimeEffect);
				}
				PlaySoundBroke();
				Destroy();
			}
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