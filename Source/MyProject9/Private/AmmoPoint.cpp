// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoPoint.h"

#include "Chel.h"

// Sets default values
AAmmoPoint::AAmmoPoint()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	Collision->SetupAttachment(RootComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AAmmoPoint::OnOverlapBegin);

	Enable = true;
}

void AAmmoPoint::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	AChel* Player = Cast<AChel>(OtherActor);
	if (Player) {
		if (Player->IsServerAuth && Enable)
		{
			Player->Ammo = 15;
			Player->StoneCountUpdate(15);
			Player->ShowStoneMulticast();

			Enable = false;

			FTimerHandle FuzeTimerHandle;
			GetWorld()->GetTimerManager().SetTimer(FuzeTimerHandle, this, &AAmmoPoint::AmmoUpdate, 10, false);
		}
	}
}

void AAmmoPoint::AmmoUpdate()
{
	TArray<AActor*>Players;
	Collision->GetOverlappingActors(Players, AChel::StaticClass());

	Enable = true;

	if (Players.Num() != 0) {
		AChel* Chel = Cast<AChel>(Players[0]);
		Chel->Ammo = 15;
		Chel->StoneCountUpdate(15);
		Chel->ShowStoneMulticast();

		Enable = false;

		FTimerHandle FuzeTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(FuzeTimerHandle, this, &AAmmoPoint::AmmoUpdate, 10, false);
	}

}


