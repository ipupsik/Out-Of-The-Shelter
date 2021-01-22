// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoPoint.h"
#include "Chel.h"
#include "Weapon_Character.h"
// Sets default values
AAmmoPoint::AAmmoPoint()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	Collision->SetupAttachment(RootComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(Collision);

	Instances = CreateDefaultSubobject<UInstancedStaticMeshComponent>("Instances");
	Mesh->SetupAttachment(Collision);

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AAmmoPoint::OnOverlapBegin);
	Enable = true;
}

void AAmmoPoint::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	AChel* Player = Cast<AChel>(OtherActor);
	if (Player) {
		if (Player->IsServerAuth && Enable && Player->CurrentWeapons[0]->LeftAmmo < Player->CurrentWeapons[0]->MaxAmmo)
		{
			Player->CurrentWeapons[0]->LeftAmmo = Player->CurrentWeapons[0]->MaxAmmo;
			Player->ChangeAmmoClients(Player->CurrentWeapons[0]->MaxAmmo, 0);
			if (Player->CurrentIndex == 0) {
				Player->SetWeaponToSlotMulticast(0);
			}
			//Player->StoneCountUpdate(Player->MaxAmmoCount);
			//Player->ShowStoneMulticast();

			Enable = false;
			HiddenMulticast(true);
			PlaySoundAmmoPoint();

			FTimerHandle FuzeTimerHandle2;
			GetWorld()->GetTimerManager().SetTimer(FuzeTimerHandle2, this, &AAmmoPoint::EnableUpdateToTrue, 15, false);
		}
	}
}

void AAmmoPoint::HiddenMulticast_Implementation(bool NewHidden)
{
	Instances->SetHiddenInGame(NewHidden);
}

void AAmmoPoint::EnableUpdateToTrue()
{
	HiddenMulticast(false);
	Enable = true;
	AmmoUpdate();
}

void AAmmoPoint::AmmoUpdate()
{
	if (Enable) {
		TArray<AActor*>Players;
		Collision->GetOverlappingActors(Players, AChel::StaticClass());
		UE_LOG(LogTemp, Warning, TEXT("Nums of Overlapping players: %d"), Players.Num());
		if (Players.Num() != 0) {

			AChel* Chel = nullptr;
			for (int i = 0; i < Players.Num(); ++i)
			{
				Chel = Cast<AChel>(Players[i]);
				if (Chel) {
					if (Chel->CurrentWeapons[0]->LeftAmmo < Chel->CurrentWeapons[0]->MaxAmmo) {
						UE_LOG(LogTemp, Warning, TEXT("FoundGoodChel: %d"), Players.Num());
						break;
					}
					else
						Chel = nullptr;
				}
			}
			if (Chel) {

				Chel->CurrentWeapons[0]->LeftAmmo = Chel->CurrentWeapons[0]->MaxAmmo;
				Chel->ChangeAmmoClients(Chel->CurrentWeapons[0]->MaxAmmo, 0);
				if (Chel->CurrentIndex == 0) {
					Chel->SetWeaponToSlotMulticast(0);
				}
				//Chel->StoneCountUpdate(Chel->MaxAmmoCount);
				//Chel->ShowStoneMulticast();

				Enable = false;
				HiddenMulticast(true);
				PlaySoundAmmoPoint();


				FTimerHandle FuzeTimerHandle2;
				GetWorld()->GetTimerManager().SetTimer(FuzeTimerHandle2, this, &AAmmoPoint::EnableUpdateToTrue, 15, false);
			}
		}
	}
}


