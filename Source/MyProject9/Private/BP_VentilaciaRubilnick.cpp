// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_VentilaciaRubilnick.h"
#include "GS.h"
#include "Chel.h"
#include "Kismet/GameplayStatics.h"
#include "VentilaciaGenerator.h"

ABP_VentilaciaRubilnick::ABP_VentilaciaRubilnick()
{
	bCanInterract = true;
	Scene = CreateDefaultSubobject<USceneComponent>("Scene");
	Scene->SetupAttachment(RootComponent);

	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	Collision->SetupAttachment(Scene);

	Item = CreateDefaultSubobject<UStaticMeshComponent>("Item");
	Item->SetupAttachment(Scene);
}

void ABP_VentilaciaRubilnick::ToggleCustomDepth(bool NewIsOutliningNow)
{
	if (bCanInterract) {
		if (this->IsOutliningNow != NewIsOutliningNow) {
			Item->SetRenderCustomDepth(NewIsOutliningNow);
			Item->MarkRenderStateDirty();
			this->IsOutliningNow = NewIsOutliningNow;
		}
	}
}

bool ABP_VentilaciaRubilnick::PickUpEventClient(AChel* Player)
{
	if (bCanInterract)
	{
		ToggleCustomDepth(false);
		Player->UserView->E_Mark->SetVisibility(ESlateVisibility::Hidden);
		bCanInterract = false;
		return true;
	}
	return false;
}

void ABP_VentilaciaRubilnick::PickUpEventServer(AChel* Player)
{
	Player->GS->VentilaciaRubilnickCount--;
	Open();
	ChangeAvaliable();
	if (Player->GS->VentilaciaRubilnickCount == 0)
	{
		Player->GS->IsVentilaciaAvaliable = true;
		TArray<AActor*>VentilaciaGenerator;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AVentilaciaGenerator::StaticClass(), VentilaciaGenerator);
		if (VentilaciaGenerator.Num() > 0)
			Cast<AVentilaciaGenerator>(VentilaciaGenerator[0])->Close();
	}
}

void ABP_VentilaciaRubilnick::ChangeAvaliable_Implementation()
{
	bCanInterract = false;
}

void ABP_VentilaciaRubilnick::OnLineTraced(AChel* Player)
{
	if (bCanInterract) {
		ToggleCustomDepth(true);
		if (!Player->UserView->E_Mark->IsVisible())
			Player->UserView->E_Mark->SetVisibility(ESlateVisibility::Visible);
	}
}