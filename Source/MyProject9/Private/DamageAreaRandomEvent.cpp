// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageAreaRandomEvent.h"
#include "Chel.h"

// Sets default values
ADamageAreaRandomEvent::ADamageAreaRandomEvent()
{
	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	Collision->SetupAttachment(RootComponent);

	Collision->OnComponentEndOverlap.AddDynamic(this, &ADamageAreaRandomEvent::OnOverlapEnd);
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ADamageAreaRandomEvent::OnOverlapBegin);
}

void ADamageAreaRandomEvent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("IN"));
	AChel* Player = Cast<AChel>(OtherActor);
	if (Player && Player->UserView) {
		if (Player->GetLocalRole() == ROLE_Authority)
		{
			UE_LOG(LogTemp, Warning, TEXT("IsNotNullptr"));
			Player->RadCoeff *= 3;
		}
		if (Player->IsPlayerOwner) {
			Player->UserView->AddIconToPanel(0);
		}
	}
}

void ADamageAreaRandomEvent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("OUT"));
	AChel* Player = Cast<AChel>(OtherActor);
	if (Player && Player->UserView) {
		if (Player->GetLocalRole() == ROLE_Authority)
		{
			Player->RadCoeff /= 3;
		}
		if (Player->IsPlayerOwner) {
			Player->UserView->RemoveIconFromPanel(0);
		}
	}
}

