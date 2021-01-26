// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RAbilitySlot.h"
#include "Kismet/GameplayStatics.h"
#include "Chel.h"
#include "ConsumableAbility.h"

void URAbilitySlot::NativeConstruct() {
	Super::NativeConstruct();

	BTN_Select->OnClicked.AddDynamic(this, &URAbilitySlot::SelectRAbility);
	BTN_Select->OnHovered.AddDynamic(this, &URAbilitySlot::HoveredRAbility);
	BTN_Select->OnUnhovered.AddDynamic(this, &URAbilitySlot::UnHoveredRAbility);
}

void URAbilitySlot::SelectRAbility()
{
	AChel* MyChel = Cast<AChel>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	MyChel->RAbilityPanel[MyChel->RAbilityTypeIndex]->UserViewSlot->SelectImage->SetVisibility(ESlateVisibility::Hidden);
	SelectImage->SetVisibility(ESlateVisibility::Visible);
	MyChel->RAbilityTypeIndex = InArrayIndex;
	MyChel->SetCurRAbilityUserView();
}

void URAbilitySlot::HoveredRAbility()
{
	AChel* MyChel = Cast<AChel>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	PromtText->SetText(MyChel->RAbilityPanel[InArrayIndex]->PromtText);
}

void URAbilitySlot::UnHoveredRAbility()
{
	PromtText->SetText(FText::FromString(""));
}