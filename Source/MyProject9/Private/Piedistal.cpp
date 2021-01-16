// Fill out your copyright notice in the Description page of Project Settings.


#include "Piedistal.h"

// Sets default values
APiedistal::APiedistal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Piedistal = CreateDefaultSubobject<UStaticMeshComponent>("Piedistal");
	Piedistal->SetupAttachment(RootComponent);
	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	Collision->SetupAttachment(Piedistal);

	PlayersCount = 0;
}

// Called when the game starts or when spawned
void APiedistal::BeginPlay()
{
	Super::BeginPlay();
	if (GetLocalRole() == ROLE_Authority) {
		GS = Cast<AGS>(GetWorld()->GetGameState());
	}
}

void APiedistal::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
	bool bFromSweep, const FHitResult& SweepResult)
{
	if (GetLocalRole() == ROLE_Authority) {
		if (!GS->IsGameStarted) {
			++PlayersCount;
			if (PlayersCount == 1) {
				GS->AcceptPiedistalAmount++;
				if (GS->AcceptPiedistalAmount == GS->MaxPlayersCount) {
					//UE_LOG(LogTemp, Warning, TEXT("11"));
					GS->GameBegin();
				}
			}
			UE_LOG(LogTemp, Warning, TEXT("%d"), GS->AcceptPiedistalAmount);
			UE_LOG(LogTemp, Warning, TEXT("%d"), PlayersCount);
		}
	}
}

void APiedistal::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (GetLocalRole() == ROLE_Authority) {
		if (!GS->IsGameStarted) {
			--PlayersCount;
			if (PlayersCount == 0)
				GS->AcceptPiedistalAmount--;
			else if (PlayersCount == 1)
				if (GS->AcceptPiedistalAmount == GS->MaxPlayersCount) {
					UE_LOG(LogTemp, Warning, TEXT(""));
					GS->GameBegin();
				}
			UE_LOG(LogTemp, Warning, TEXT("%d"), GS->AcceptPiedistalAmount);
			UE_LOG(LogTemp, Warning, TEXT("%d"), PlayersCount);
		}
	}
}
