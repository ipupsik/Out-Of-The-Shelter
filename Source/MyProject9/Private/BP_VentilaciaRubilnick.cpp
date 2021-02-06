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

	IsEnableWhen3Player = true;
}

void ABP_VentilaciaRubilnick::ToggleCustomDepth(bool NewIsOutliningNow, AChel* Player)
{
	if (bCanInterract) {
		if (this->IsOutliningNow != NewIsOutliningNow) {
			Item->SetRenderCustomDepth(NewIsOutliningNow);
			Item->MarkRenderStateDirty();
			this->IsOutliningNow = NewIsOutliningNow;
		}
	}
	if (!NewIsOutliningNow)
	{
		Player->UserView->CountLeftPromt->SetVisibility(ESlateVisibility::Hidden);
	}
}

bool ABP_VentilaciaRubilnick::PickUpEventClient(AChel* Player)
{
	if (bCanInterract)
	{
		ToggleCustomDepth(false, Player);
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
		Player->GS->OffCollisionRubilnici();

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
		ToggleCustomDepth(true, Player);
		if (!Player->UserView->E_Mark->IsVisible())
			Player->UserView->E_Mark->SetVisibility(ESlateVisibility::Visible);
		if (Player->GI->bIsEnabledPrompt) {
			Player->UserView->PropmptTextInterract->SetText(PromptText);
			Player->UserView->PropmptTextInterract->SetVisibility(ESlateVisibility::Visible);
			Player->UserView->CountLeftPromt->SetVisibility(ESlateVisibility::Visible);
			FString NewString = FText::AsNumber(Player->GS->MaxVentilaciaRubilnickCount - Player->GS->VentilaciaRubilnickCount).ToString();
			NewString += "/";
			NewString += FText::AsNumber(Player->GS->MaxVentilaciaRubilnickCount).ToString();
			Player->UserView->CountLeftPromt->SetText(FText::FromString(NewString));
			Player->UserView->CountLeftPromt->SetColorAndOpacity(MyColor);
		}
	}
	else
	{
		if (Player->GI->bIsEnabledPrompt) {
			Player->UserView->CountLeftPromt->SetVisibility(ESlateVisibility::Visible);
			FString NewString = FText::AsNumber(Player->GS->MaxVentilaciaRubilnickCount - Player->GS->VentilaciaRubilnickCount).ToString();
			NewString += "/";
			NewString += FText::AsNumber(Player->GS->MaxVentilaciaRubilnickCount).ToString();
			Player->UserView->CountLeftPromt->SetText(FText::FromString(NewString));
			Player->UserView->CountLeftPromt->SetColorAndOpacity(MyColor);
		}
	}
}