// Fill out your copyright notice in the Description page of Project Settings.


#include "AreaCollision.h"
#include "Chel.h"

// Sets default values
AAreaCollision::AAreaCollision()
{
	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	Collision->SetupAttachment(RootComponent);

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AAreaCollision::OnOverlapBegin);
	Collision->OnComponentEndOverlap.AddDynamic(this, &AAreaCollision::OnOverlapEnd);

}

void AAreaCollision::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	AChel* Player = Cast<AChel>(OtherActor);
	if (Player) {
		if (Player->IsPlayerOwner) {
			if (AreaType != 3) { //Не в двери выхода шелтора
				if (Player->IsPlayerOwner && !Player->GS->AreaClosed[AreaType]) {
					if (AreaType == 1 && !Player->GS->IsShelterAvaliable)
						return;
					if (AreaType == 2 && !Player->GS->IsVentilaciaAvaliable)
						return;
					if (AreaType == 0 && !Player->GS->IsCanalizaciaAvaliable)
						return;
					Player->AreaCode = AreaType;
					if (!Player->GS->AreaAvaliables[AreaType])
					{
						if (Player->DoesHave[AreaType])
							Player->UserView->HoldText->SetVisibility(ESlateVisibility::Visible);
					}
					else
					{
						if (AreaType != 1) {
							Player->UserView->EscapeText->SetVisibility(ESlateVisibility::Visible);
						}
					}
				}
			}
			else {
				if (Player->IsPlayerOwner && !Player->GS->AreaClosed[1]) {
					Player->AreaCode = AreaType;
					if (Player->GS->AreaAvaliables[1]) {
						Player->UserView->EscapeText->SetVisibility(ESlateVisibility::Visible);
					}
				}
			}
		}
	}
}

void AAreaCollision::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AChel* Player = Cast<AChel>(OtherActor);
	if (Player) {
		if (Player->IsPlayerOwner) {
			if (AreaType != 3) { //Не в двери выхода шелтора
				if (Player->IsPlayerOwner && !Player->GS->AreaClosed[AreaType]) {
					Player->AreaCode = -1;
					if (!Player->GS->AreaAvaliables[AreaType])
					{
						Player->IsSuccessOpening = false;
						Player->UserView->StopAllAnimations();
						Player->UserView->PB_Opening->SetVisibility(ESlateVisibility::Hidden);
						Player->UserView->HoldText->SetVisibility(ESlateVisibility::Hidden);
					}
					else
					{
						if (AreaType != 1)
							Player->UserView->EscapeText->SetVisibility(ESlateVisibility::Hidden);
					}
				}
			}
			else {
				if (Player->IsPlayerOwner && !Player->GS->AreaClosed[1])
				{
					Player->AreaCode = -1;
					if (Player->GS->AreaAvaliables[1]) {
						Player->UserView->EscapeText->SetVisibility(ESlateVisibility::Hidden);
					}
				}
			}
		}
	}
}


