// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/VerstakWidget_Item.h"
#include "Chel.h"
#include "Weapon_Level.h"
#include "Weapon_Character.h"

void UVerstakWidget_Item::NativeConstruct() {
	UUserWidget::NativeConstruct();
}

void UVerstakWidget_Item::CreateEvent(AChel* Creator, int32 CostItem){
	if (CreatedItemClass->IsChildOf(AWeapon_Character::StaticClass())) {
		if (Creator->CurrentWeapons[1]) {
			if (Creator->CurrentWeapons[1]->GetClass() == CreatedItemClass) {
				if (Creator->CurrentWeapons[1]->LeftAmmo == Creator->CurrentWeapons[1]->MaxAmmo)
					return;
				if (Creator->CurrentWeapons[1]->LeftAmmo + 1 <= Creator->CurrentWeapons[1]->MaxAmmo) {
					Creator->ChangeAmmoServer(Creator->CurrentWeapons[1]->LeftAmmo + 1, 1);
					if (Creator->CurrentIndex == 0 && Creator->CurrentWeapons[0]->LeftAmmo == 0) {
						Creator->SetWeaponToSlotServer(1);
					}
					else if (Creator->CurrentIndex == 1) {
						Creator->RefreshWidgetAmmoOwning(Creator->CurrentWeapons[1]->LeftAmmo, Creator->CurrentWeapons[1]->MaxAmmo, 1);
					}
				}
				Creator->AmountDetails -= CostItem;
			}
			else {
				if (Creator->CurrentWeapons[1]->LeftAmmo > 0) {
					Creator->DropSpecialGun_Server();
				}
				UE_LOG(LogTemp, Warning, TEXT("I`m on Server and going to Multicast"));
				Creator->CreateWeaponServer(CreatedItemClass, 1, 1);
				Creator->AmountDetails -= CostItem;
			}
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("I`m on Server and going to Multicast"));
			Creator->CreateWeaponServer(CreatedItemClass, 1, 1);
			Creator->AmountDetails -= CostItem;
		}
	}
	else {
		if (Creator->NewRAbility(CreatedItemClass))
			Creator->AmountDetails -= CostItem;
	}
	Creator->RefreshAmountDetails();
}
