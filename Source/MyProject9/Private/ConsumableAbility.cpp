// Fill out your copyright notice in the Description page of Project Settings.


#include "ConsumableAbility.h"
#include "Chel.h"

void UConsumableAbility::UseAbilityClient(AChel* Player)
{

}

void UConsumableAbility::UseAbilityServer(AChel* Player)
{
}

void UConsumableAbility::SetAbilityToSlot()
{
	FSlateBrush NewBrush;
	NewBrush.SetResourceObject(Icon);
	UserViewSlot->AbilityImage->SetBrush(NewBrush);
	CurCount = 1;
	UpdateCount();
	UserViewSlot->SetVisibility(ESlateVisibility::Visible);
}

void UConsumableAbility::SetCurRAbilityUserView(AChel* Player)
{
	Player->UserView->CurRSlot->AbilityImage->SetBrush(UserViewSlot->AbilityImage->Brush);
	Player->UserView->CurRSlot->CountText->SetText(FText::AsNumber(CurCount));
}

void UConsumableAbility::UpdateCount()
{
	UserViewSlot->CountText->SetText(FText::AsNumber(CurCount));
}
