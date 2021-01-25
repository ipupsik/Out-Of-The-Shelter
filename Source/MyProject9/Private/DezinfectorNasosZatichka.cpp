// Fill out your copyright notice in the Description page of Project Settings.


#include "DezinfectorNasosZatichka.h"
#include "DezinfectorNasos.h"
#include "Chel.h"

// Sets default values
ADezinfectorNasosZatichka::ADezinfectorNasosZatichka()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DoesLock = true;
	DoesPlayAnim = false;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	Scene->SetupAttachment(RootComponent);

	Zatichka = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Zatichka"));
	Zatichka->SetupAttachment(Scene);

	PS = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PS"));
	PS->SetupAttachment(Scene);
}

void ADezinfectorNasosZatichka::PickUpEventServer(AChel* Player)
{
	if (!DoesPlayAnim && Nasos->bIsAvaliable)
	{
		if (DoesLock) 
		{
			SwitchAnimUp();
			Nasos->CurTurnOffCount++;
		}
		else
		{
			SwitchAnimDown();
			Nasos->CurTurnOffCount--;
			if (Nasos->CurTurnOffCount == 0)
			{
				Nasos->TurnOn();
			}
		}
	}
}

bool ADezinfectorNasosZatichka::PickUpEventClient(AChel* Player)
{
	if (Nasos->bIsAvaliable)
		return true;
	return false;
}

void ADezinfectorNasosZatichka::OnLineTraced(AChel* Player)
{
	if (Nasos->bIsAvaliable) {
		ToggleCustomDepth(true, Player);
		if (!Player->UserView->E_Mark->IsVisible())
			Player->UserView->E_Mark->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		ToggleCustomDepth(false);
		if (Player->UserView->E_Mark->IsVisible())
			Player->UserView->E_Mark->SetVisibility(ESlateVisibility::Hidden);
	}
}

void ADezinfectorNasosZatichka::ToggleCustomDepth(bool NewIsOutliningNow, AChel* Player)
{
	if (this->IsOutliningNow != NewIsOutliningNow) {
		Zatichka->SetRenderCustomDepth(NewIsOutliningNow);
		Zatichka->MarkRenderStateDirty();
		this->IsOutliningNow = NewIsOutliningNow;
	}
}
