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
	Mesh->SetupAttachment(Collision);

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AAmmoPoint::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AAmmoPoint::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AAmmoPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation({ 0.0f, DeltaTime * 50, 0.0f });
}

void AAmmoPoint::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	AChel* Player = Cast<AChel>(OtherActor);
	if (Player) {
		if (Player->IsServerAuth)
		{
			Player->Health = 0;
			Player->StoneCountUpdate();
			Collision->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);

			FTimerHandle FuzeTimerHandle;
			GetWorld()->GetTimerManager().SetTimer(FuzeTimerHandle, this, &AAmmoPoint::AmmoUpdate, 10, false);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Spectator Overlapp instead Chel"))
	}
}

void AAmmoPoint::AmmoUpdate()
{
	TArray<AActor*>Players;
	Collision->GetOverlappingActors(Players, AChel::StaticClass());

	if (Players.Num() != 0) {
		AChel* Chel = Cast<AChel>(Players[0]);
		Chel->Health = 0;
		Chel->StoneCountUpdate();
		Collision->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);

		FTimerHandle FuzeTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(FuzeTimerHandle, this, &AAmmoPoint::AmmoUpdate, 10, false);
	}
	else
	{
		SetActorHiddenInGame(false);
		Collision->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
	}
	Players.Empty();
}


