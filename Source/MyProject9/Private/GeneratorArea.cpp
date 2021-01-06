// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneratorArea.h"
#include "Net/UnrealNetwork.h"
#include "PromptCollisionArea.h"
#include "Chel.h"


// Sets default values
AGeneratorArea::AGeneratorArea()
{
	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	Collision->SetupAttachment(RootComponent);

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AGeneratorArea::OnOverlapBegin);
	Collision->OnComponentEndOverlap.AddDynamic(this, &AGeneratorArea::OnOverlapEnd);

	IsAvalible = true;
}

void AGeneratorArea::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGeneratorArea, Stadiya);
	DOREPLIFETIME(AGeneratorArea, IsAvalible);
}

void AGeneratorArea::RefreshGenerator()
{
	IsAvalible = true;

	for (auto& it : PromtCollisionGenerator)
	{
		it->bISAvaliable = true;
	}

	TArray<AActor*>Chelix;
	Collision->GetOverlappingActors(Chelix, AChel::StaticClass());
	for (auto& it : Chelix)
	{
		Cast<AChel>(it)->RefreshGeneratorArea();
	}
	ChangeLampochka(1);
}


void AGeneratorArea::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	AChel* Player = Cast<AChel>(OtherActor);
	if (Player) {
		Player->GenAreaObj = this;
		if (Player->UserView) {
			Player->AreaCode = 6;
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
		if (Player->UserView) {
			Player->AreaCode = -1;
			Player->TickEnableGeneratorWidget = false;
			Player->UserView->HoldText->SetVisibility(ESlateVisibility::Hidden);
			Player->UserView->AreaUsedText->SetVisibility(ESlateVisibility::Hidden);
			Player->GeneratorView->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void AGeneratorArea::DoSomethinkGen() {
	IsAvalible = false;
	Stadiya = 0;
	ChangeLampochka(0);
}

void AGeneratorArea::ChangeLampochka_Implementation(int32 type)
{
	switch (type) {
	case 0: 
	{
		Lamp->LampochkaModel->SetMaterial(0, Lamp->MaterialOn);
		break;
	}
	case 1:
	{
		Lamp->LampochkaModel->SetMaterial(0, Lamp->MaterialOff);
		break;
	}
	}
}
