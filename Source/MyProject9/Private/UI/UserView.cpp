// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UserView.h"
#include "Kismet/GameplayStatics.h"
#include "Chel.h"
#include "Ventil.h"

void UUserView::NativeConstruct() {
	Super::NativeConstruct();
	IsAwake = true;
	ArraySwitcher.Init(nullptr, 3);
	ArraySwitcher[0] = WS_Boltorez;
	ArraySwitcher[1] = WS_KeyShelter;
	ArraySwitcher[2] = WS_Otvertka;

	ArrayCacheKey.Init(nullptr, 3);
	ArrayCacheKey[0] = KeyLeft_Bronze;
	ArrayCacheKey[1] = KeyLeft_Silver;
	ArrayCacheKey[2] = KeyLeft_Gold;
}

void UUserView::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
	UE_LOG(LogTemp, Warning, TEXT("Ya v Animacii"))
	if (Animation == CanalizaciaAnim)
	{
		if (Player->IsSuccessOpening && !Player->GS->AreaAvaliables[0]) {
			Player->StuffAvaliableUpdate(0);
			HoldText->SetVisibility(ESlateVisibility::Hidden);
			EscapeText->SetVisibility(ESlateVisibility::Visible);
			Player->DeleteArrowDelayBoltorez();
			Player->PlayerOpenAreaUpdate(0);
		}
	}
	else if (Animation == ShelterAnim)
	{
		if (Player->IsSuccessOpening && !Player->GS->AreaAvaliables[1]) {
			Player->StuffAvaliableUpdate(1);
			HoldText->SetVisibility(ESlateVisibility::Hidden);
			Player->PlayerOpenAreaUpdate(1);
			Player->DeleteArrowDelayKeyShelter();
		}
	}
	else if (Animation == VentilaciaAnim)
	{
		if (Player->IsSuccessOpening && !Player->GS->AreaAvaliables[2]) {
			Player->StuffAvaliableUpdate(2);
			HoldText->SetVisibility(ESlateVisibility::Hidden);
			EscapeText->SetVisibility(ESlateVisibility::Visible);
			Player->DeleteArrowDelayOtvertka();
			Player->PlayerOpenAreaUpdate(2);
		}
	}
	else if (Animation == OpenAreaAnim) {
		PB_Opening->SetPercent(0);
		PB_Opening->SetVisibility(ESlateVisibility::Hidden);
		TimeLeft->SetVisibility(ESlateVisibility::Hidden);
		if (Player->LastInteractiveItem && Player->IsSuccessOpening) {
				Player->CallEnableGasVent();
		}
//		if (Cast<AOpenArea>(Player->LastItem) && Player->IsSuccessOpening) {
//			Player->CallDoThomethinkArea();
//		}
	}
	PB_Opening->SetVisibility(ESlateVisibility::Hidden);
	TimeLeft->SetVisibility(ESlateVisibility::Hidden);
}
void UUserView::AddDoubleRadiationEffect() {
	
	UUserWidget* Image = CreateWidget(GetWorld(), RadiationImage);
	UHorizontalBoxSlot* Hor_slot = Cast<UHorizontalBoxSlot>(Effects_Bar->AddChild(Image));
	Hor_slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
	Hor_slot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
	FSlateChildSize InSize = FSlateChildSize(ESlateSizeRule::Fill);
	InSize.Value = 1.0f;
	Hor_slot->SetSize(InSize);
}

void UUserView::DisableDoubleRadiationEffect()
{
	TArray<UWidget*> EffectsWidgets = Effects_Bar->GetAllChildren();
	UE_LOG(LogTemp, Warning, TEXT("DisableEffect"))
	for (auto& it : EffectsWidgets) {
		UE_LOG(LogTemp, Warning, TEXT("Child"))
		if (Cast<URadiationWidget>(it) != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Remove"))
			it->RemoveFromParent();
			return;
		}
	}
}
