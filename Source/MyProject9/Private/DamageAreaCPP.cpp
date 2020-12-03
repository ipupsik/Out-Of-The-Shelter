// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageAreaCPP.h"
#include "Chel.h"
// Sets default values
ADamageAreaCPP::ADamageAreaCPP()
{
	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	Collision->SetupAttachment(RootComponent);

	Collision->OnComponentEndOverlap.AddDynamic(this, &ADamageAreaCPP::ComponentOverlapEnd);
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ADamageAreaCPP::OnOverlapBegin);

}

void ADamageAreaCPP::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (GetLocalRole() == ROLE_Authority)
	{
		AChel* Player = Cast<AChel>(OtherActor);
		if (Player) {
			Player->RadCoeff *= 2;
			Player->AddDoubleRadiationWidget();
		}
		
	}
}

void ADamageAreaCPP::ComponentOverlapEnd(UPrimitiveComponent * OverlappedComponent, AActor * OverlappedActor, UPrimitiveComponent * OtherActor, int32 OtherBodyIndex)
{
	if (GetLocalRole() == ROLE_Authority)
	{
		AChel* Player = Cast<AChel>(OtherActor);
		if (Player) {
			Player->RadCoeff /= 2;
			Player->DisableDoubleRadiationWidget();
		}
		
	}
}