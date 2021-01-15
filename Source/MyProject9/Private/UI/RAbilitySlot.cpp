// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RAbilitySlot.h"
#include "Kismet/GameplayStatics.h"
#include "Chel.h"

void URAbilitySlot::NativeConstruct() {
	Super::NativeConstruct();

	BTN_Select->OnClicked.AddDynamic(this, &URAbilitySlot::SelectRAbility);
	AbilityType = -1;
	Count = 0;
	InArrayIndex = -1;
}

void URAbilitySlot::SelectRAbility()
{
	Cast<AChel>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->RAbilityTypeIndex = InArrayIndex;
	UE_LOG(LogTemp, Warning, TEXT("AbilityType - %d"), AbilityType)
}