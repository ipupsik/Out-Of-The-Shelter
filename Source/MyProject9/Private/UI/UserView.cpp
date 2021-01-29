// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UserView.h"
#include "Kismet/GameplayStatics.h"
#include "Chel.h"
#include "Ventil.h"

enum {
	RadiationRandomEvent,
	RadiationVentil,
	Invisible,
	ImmortalDamage,
	DoubleDamage,
	DecreaseRadiation,
	InvertMovement
};

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
			//HoldText->SetVisibility(ESlateVisibility::Hidden);
			//EscapeText->SetVisibility(ESlateVisibility::Visible);
			if (Player->CurCoreArea)
				PropmptTextArea->SetText(Player->CurCoreArea->AreaOpenAndCanEscape);
			Player->DeleteArrowDelayBoltorez();
			Player->PlayerOpenAreaUpdate(0);
		}
	}
	else if (Animation == ShelterAnim)
	{
		if (Player->IsSuccessOpening && !Player->GS->AreaAvaliables[1]) {
			Player->StuffAvaliableUpdate(1);
			//HoldText->SetVisibility(ESlateVisibility::Hidden);
			if (!Player->LastInteractiveItem)
				E_Mark->SetVisibility(ESlateVisibility::Hidden);
			if (Player->CurCoreArea)
				PropmptTextArea->SetText(Player->CurCoreArea->AreaOpenAndCanEscape);
			Player->PlayerOpenAreaUpdate(1);
			Player->DeleteArrowDelayKeyShelter();
		}
	}
	else if (Animation == VentilaciaAnim)
	{
		if (Player->IsSuccessOpening && !Player->GS->AreaAvaliables[2]) {
			Player->StuffAvaliableUpdate(2);
			//HoldText->SetVisibility(ESlateVisibility::Hidden);
			//EscapeText->SetVisibility(ESlateVisibility::Visible);
			if (Player->CurCoreArea)
				PropmptTextArea->SetText(Player->CurCoreArea->AreaOpenAndCanEscape);
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
/*void UUserView::AddDoubleRadiationEffect() {
	
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
*/

void UUserView::AddIconToPanel(int32 IdEffect) {
	if (IdEffect >= 0) {
		UUserWidget* Image = nullptr;
		switch (IdEffect) {
		case RadiationRandomEvent:
			Image = CreateWidget(GetWorld(), RadiationRandomEvent_Class);
			break;
		case RadiationVentil:
			Image = CreateWidget(GetWorld(), RadiationVentil_Class);
			break;
		case Invisible:
			Image = CreateWidget(GetWorld(), Invisible_Class);
			break;
		case ImmortalDamage:
			Image = CreateWidget(GetWorld(), Immortal_Class);
			break;
		case DoubleDamage:
			Image = CreateWidget(GetWorld(), DoubleDamage_Class);
			break;
		case DecreaseRadiation:
			Image = CreateWidget(GetWorld(), DecreaseRadiation_Class);
			break;
		case InvertMovement:
			Image = CreateWidget(GetWorld(), InvertMovement_Class);
			break;
		default:
			return;
			break;
		}

		UIconWidget* Icon = Cast<UIconWidget>(Image);
		if (Icon) {
			Icon->Identificator = IdEffect;
			UHorizontalBoxSlot* Hor_slot = Cast<UHorizontalBoxSlot>(Effects_Bar->AddChild(Icon));
			Hor_slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
			Hor_slot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
			FSlateChildSize InSize = FSlateChildSize(ESlateSizeRule::Fill);
			InSize.Value = 1.0f;
			Hor_slot->SetSize(InSize);
		}
	}
}

void UUserView::RemoveIconFromPanel(int32 IdEffect) {
	TArray<UWidget*> EffectsWidgets = Effects_Bar->GetAllChildren();
	for (auto& it : EffectsWidgets) {
		UIconWidget* Icon = Cast<UIconWidget>(it);
		if (Icon && Icon->Identificator == IdEffect)
		{
			Icon->RemoveFromParent();
			return;
		}
	}
}