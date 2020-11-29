// Fill out your copyright notice in the Description page of Project Settings.


#include "Stone.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Chel.h"

// Sets default values
AStone::AStone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));

	Stone = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Stone"));
	Stone->SetupAttachment(RootComponent);

	Stone->OnComponentBeginOverlap.AddDynamic(this, &AStone::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AStone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStone::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	if (GetLocalRole() == ROLE_Authority) {
		AChel* Player = Cast<AChel>(OtherActor);
		if (Player->Index != Index)
		{
			Player->StoneAttack(Index);
			TArray<AActor*>Players;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), AChel::StaticClass(), Players);
			for (int i = 0; i < Players.Num(); i++) {
				AChel* Chel = Cast<AChel>(Players[i]);
				if (Chel->Index == Index)
				{
					Chel->AddHitMarker();
					break;
				}
			}
			Destroy();
		}
	}
}