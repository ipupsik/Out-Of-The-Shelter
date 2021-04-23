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
	AChel* Player = Cast<AChel>(OtherActor);
	if (Player && Player->UserView) {
		if (Player->GetLocalRole() == ROLE_Authority)
		{
			UE_LOG(LogTemp, Warning, TEXT("IsNotNullptr"));
			Player->RadCoeff *= 2;
			//Player->AddDoubleRadiationWidget();
		}
		if (Player->IsPlayerOwner) {
			Player->UserView->AddIconToPanel(1);
		}
	}
}

void ADamageAreaCPP::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("OUT"));
	AChel* Player = Cast<AChel>(OtherActor);
	if (Player && Player->UserView) {
		if (Player->GetLocalRole() == ROLE_Authority)
		{
			Player->RadCoeff /= 2;
			//Player->DisableDoubleRadiationWidget();
		}
		if (Player->IsPlayerOwner) {
			Player->UserView->RemoveIconFromPanel(1);
		}
	}
}