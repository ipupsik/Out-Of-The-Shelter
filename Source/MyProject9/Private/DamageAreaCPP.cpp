// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageAreaCPP.h"
#include "Chel.h"
// Sets default values
ADamageAreaCPP::ADamageAreaCPP()
{
	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	Collision->SetupAttachment(RootComponent);

	Collision->OnComponentEndOverlap.AddDynamic(this, &ADamageAreaCPP::OnOverlapEnd);
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ADamageAreaCPP::OnOverlapBegin);

}
void ADamageAreaCPP::BeginPlay() {
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Created Damage Area"));
}
void ADamageAreaCPP::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("IN"));
	if (GetLocalRole() == ROLE_Authority)
	{
		AChel* Player = Cast<AChel>(OtherActor);
		if (Player) {
			UE_LOG(LogTemp, Warning, TEXT("IsNotNullptr"));
			Player->RadCoeff *= 2;
			Player->AddDoubleRadiationWidget();
		}
	}
}

void ADamageAreaCPP::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("OUT"));
	if (GetLocalRole() == ROLE_Authority)
	{
		AChel* Player = Cast<AChel>(OtherActor);
		if (Player) {
			Player->RadCoeff /= 2;
			Player->DisableDoubleRadiationWidget();
		}
		
	}
}