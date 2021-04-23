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
		if (Player->IsServerAuth)
		{
			Player->GenAreaObj = this;
		}
		if (Player->IsPlayerOwner && Player->UserView) {
			Player->GenAreaObj = this;
			if (IsAvalible) {
				Player->UserView->E_Mark->SetVisibility(ESlateVisibility::Visible);
				Player->UserView->PropmptTextArea->SetText(PromptGenNotRepairing);
				if (Player->GI->bIsEnabledPrompt) {
					Player->UserView->PropmptTextArea->SetVisibility(ESlateVisibility::Visible);
				}
			}
			else {
				Player->UserView->PropmptTextArea->SetText(PromptGenTextNotActive);
				if (Player->GI->bIsEnabledPrompt) {
					Player->UserView->PropmptTextArea->SetVisibility(ESlateVisibility::Visible);
				}

			}
		}
	}
}

void AGeneratorArea::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	AChel* Player = Cast<AChel>(OtherActor);
	if (Player) {
		if (Player->IsServerAuth)
		{
			Player->GenAreaObj = nullptr;
		}
		if (Player->IsPlayerOwner && Player->UserView) {
			Player->GenAreaObj = nullptr;
			Player->TickEnableGeneratorWidget = false;
			Player->UserView->E_Mark->SetVisibility(ESlateVisibility::Hidden);
			if (Player->GI->bIsEnabledPrompt) {
				Player->UserView->PropmptTextArea->SetVisibility(ESlateVisibility::Hidden);
			}
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

void AGeneratorArea::PressedEGenerator(AChel* Player) {
	if (Player->GenAreaObj) {
		if (Player->GenAreaObj->IsAvalible && Player->UserView) {
			if (Player->GeneratorView->IsVisible()) {
				if (Player->GeneratorView->Corretca->Value >= Player->GeneratorView->PB_Repair->Percent) {
					Player->ChangeGeneratorStas();
				}
				else {
					Player->ChangePBPosition(Player->GenAreaObj->Stadiya);
					Player->OutlineBad_Server();//Здесь могла быть ваша логика с обводкой конкретного челика для всех остальных, но уже 12 часов ночи, сори, бб
				}
			}
			else {
				Player->UserView->E_Mark->SetVisibility(ESlateVisibility::Hidden);
				Player->UserView->PropmptTextArea->SetText(PromptGenTextRepairing);
				Player->GeneratorView->SetVisibility(ESlateVisibility::Visible);
				Player->ChangePBPosition(Player->GenAreaObj->Stadiya);
				Player->TickEnableGeneratorWidget = true;
			}
		}
	}
}