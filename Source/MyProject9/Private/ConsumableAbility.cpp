// Fill out your copyright notice in the Description page of Project Settings.


#include "ConsumableAbility.h"
#include "Chel.h"
#include "Kismet/GameplayStatics.h"

bool UConsumableAbility::UseAbilityClient(AChel* Player)
{
	Player->PlayRAbilitySound(MySoundWave);
	Player->UserView->AddIconToPanel(IdentificatorIcon);
	return true;
}

void UConsumableAbility::UseAbilityServer(AChel* Player)
{

}

FVector UConsumableAbility::GetCacheScale3D(int32 CacheIndex)
{
	return FVector();
}

FRotator UConsumableAbility::GetCacheRotation(int32 CacheIndex)
{
	return FRotator();
}

FVector UConsumableAbility::GetCacheLocation(int32 CacheIndex)
{
	return FVector();
}

void UConsumableAbility::SetAbilityToSlot()
{
	FSlateBrush NewBrush;
	NewBrush.SetResourceObject(Icon);
	UserViewSlot->AbilityImage->SetBrush(NewBrush);
	UserViewSlot->SetVisibility(ESlateVisibility::Visible);
}

void UConsumableAbility::SetCurRAbilityUserView(AChel* Player)
{
	Player->UserView->CurRSlot->AbilityImage->SetBrush(UserViewSlot->AbilityImage->Brush);
	Player->RAbilityPanel[Player->RAbilityTypeIndex]->UserViewSlot->SelectImage->SetVisibility(ESlateVisibility::Visible);
	Player->UserView->CurRSlot->PromtText->SetVisibility(ESlateVisibility::Visible);
	Player->UserView->CurRSlot->PromtText->SetText(PromtText);
}

void UConsumableAbility::ResetCurRAbilityUserView(AChel* Player)
{
	if (Player->RAbilityTypeIndex == UserViewSlot->InArrayIndex)
	{
		SetCurRAbilityUserView(Player);
	}
}

void UConsumableAbility::ResetAbility()
{
	FSlateBrush NewBrush;
	NewBrush.SetResourceObject(Icon);
	UserViewSlot->AbilityImage->SetBrush(NewBrush);
}