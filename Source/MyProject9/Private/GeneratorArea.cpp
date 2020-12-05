// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneratorArea.h"
#include "Net/UnrealNetwork.h"
#include "Chel.h"


// Sets default values
AGeneratorArea::AGeneratorArea()
{
	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	Collision->SetupAttachment(RootComponent);

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AGeneratorArea::OnOverlapBegin);
	Collision->OnComponentEndOverlap.AddDynamic(this, &AGeneratorArea::OnOverlapEnd);



}

void AGeneratorArea::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGeneratorArea, Stadiya);
	DOREPLIFETIME(AGeneratorArea, IsAvalible);
}


void AGeneratorArea::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){
	AChel* Player = Cast<AChel>(OtherActor);
	if (Player) {
		Player->GenAreaObj = this;
		Player->AreaCode = 6;
		if (Player->UserView) {
			if (IsAvalible) {
				Player->UserView->HoldText->SetVisibility(ESlateVisibility::Visible);
			}
			else {
				Player->UserView->AreaUsedText->SetVisibility(ESlateVisibility::Visible);
			}
		}
	}

}

void AGeneratorArea::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	AChel* Player = Cast<AChel>(OtherActor);
	if (Player) {
		Player->GenAreaObj = nullptr;
		Player->AreaCode = -1;
		if (Player->UserView) {
			Player->UserView->HoldText->SetVisibility(ESlateVisibility::Hidden);
			Player->UserView->AreaUsedText->SetVisibility(ESlateVisibility::Hidden);
			Player->GeneratorView->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void AGeneratorArea::DoSomethinkGen() {
	IsAvalible = false;
	Stadiya = 0;
	ChangeLampochka();
}

void AGeneratorArea::ChangeLampochka_Implementation()
{
	Lamp->LampochkaModel->SetMaterial(0, Lamp->MaterialOn);

}
