// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenAreaCPP.h"
#include "Chel.h"

// Sets default values
AOpenAreaCPP::AOpenAreaCPP()
{

	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	Collision->SetupAttachment(RootComponent);

	Collision->OnComponentEndOverlap.AddDynamic(this, &AOpenAreaCPP::ComponentOverlapEnd);
	Collision->OnComponentBeginOverlap.AddDynamic(this, &AOpenAreaCPP::OnOverlapBegin);

	bIsAvaliable = true;
}

void AOpenAreaCPP::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AChel* Player = Cast<AChel>(OtherActor);
	if (Player != nullptr) {	
		Player->OpenAreaObj = this;
		UUserView* PlayerView = Player->UserView;
		if (PlayerView != nullptr) {
			Player->AreaCode = areaType;
			if (bIsAvaliable) {
				PlayerView->HoldText->SetVisibility(ESlateVisibility::Visible);
			}
			else {
				PlayerView->AreaUsedText->SetVisibility(ESlateVisibility::Visible);
			}
		}
	}
}

void AOpenAreaCPP::ComponentOverlapEnd(UPrimitiveComponent * OverlappedComponent, AActor * OverlappedActor, UPrimitiveComponent * OtherActor, int32 OtherBodyIndex)
{
	AChel* Player = Cast<AChel>(OtherActor);
	if (Player != nullptr) {
		Player->OpenAreaObj = nullptr;
		UUserView* PlayerView = Player->UserView;
		if (PlayerView != nullptr) {
			Player->AreaCode = -1;
			PlayerView->HoldText->SetVisibility(ESlateVisibility::Hidden);
			PlayerView->AreaUsedText->SetVisibility(ESlateVisibility::Hidden);
			PlayerView->StopAllAnimations();
		}
	}
}

void AOpenAreaCPP::DoSomethink()
{
}
