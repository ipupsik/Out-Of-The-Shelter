// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon_Level.h"
#include "Weapon_Character.h"

AWeapon_Level::AWeapon_Level() {
	
}

void AWeapon_Level::PickUpEventClient(AChel* Player) {
	Amount = 1;
}

void AWeapon_Level::ChangeAmount_Implementation(int32 NewAmount)
{
	if (GetLocalRole() != ROLE_Authority)
		Amount = NewAmount;
}

void AWeapon_Level::PickUpEventServer(AChel* Player) { //¬ызываетс€ из PickUp серверовского чела
	if (Player->CurrentWeapons[1]) {
		if (Player->CurrentWeapons[1]->StaticClass() == WeaponClass) {
			if (Player->CurrentWeapons[1]->LeftAmmo == Player->CurrentWeapons[1]->MaxAmmo)
				return;
			if (Player->CurrentWeapons[1]->LeftAmmo + Amount <= Player->CurrentWeapons[1]->MaxAmmo) {
				Player->CurrentWeapons[1]->LeftAmmo += Amount;
				Player->ChangeAmmoOwner(Player->CurrentWeapons[1]->LeftAmmo);
				if (Player->CurrentIndex == 0 && Player->CurrentWeapons[0]->LeftAmmo == 0) {
					Player->SetWeaponToSlotMulticast(1);
					Player->RefreshWidgetAmmoOwningClient(Player->CurrentWeapons[0]->LeftAmmo, Player->CurrentWeapons[0]->MaxAmmo, 1);
				}
				else if (Player->CurrentIndex == 1) {
					Player->RefreshWidgetAmmoOwningClient(Player->CurrentWeapons[0]->LeftAmmo, Player->CurrentWeapons[0]->MaxAmmo, 1);
				}
				Destroy();
			}
			else {
				ChangeAmount(Amount - Player->CurrentWeapons[1]->LeftAmmo);
				Player->CurrentWeapons[1]->LeftAmmo = Player->CurrentWeapons[1]->MaxAmmo;

				if (Player->CurrentIndex == 0 && Player->CurrentWeapons[0]->LeftAmmo == 0) {
					Player->SetWeaponToSlotMulticast(1);
					Player->RefreshWidgetAmmoOwningClient(Player->CurrentWeapons[0]->LeftAmmo, Player->CurrentWeapons[0]->MaxAmmo, 1);
				}
				else if (Player->CurrentIndex == 1) {
					Player->RefreshWidgetAmmoOwningClient(Player->CurrentWeapons[0]->LeftAmmo, Player->CurrentWeapons[0]->MaxAmmo, 1);
				}
			}

		}
		else if (Player->CurrentWeapons[1]->LeftAmmo > 0) {
			Player->CurrentWeapons[1]->DropItem();
			CreateWeapon(Player->Index);
		}
	}
	else {
		CreateWeapon(Player->Index);
	}
}

void AWeapon_Level::CreateWeapon_Implementation(int32 IndexPlayer) { //Multicast событие, создающее оружие у всех челов
	AChel* Player = nullptr;

	TArray<AActor*> Chels;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AChel::StaticClass(), Chels);
	for (auto& it : Chels) {
		AChel* CurChel = Cast<AChel>(it);
		if (CurChel->Index == IndexPlayer) {
			Player = CurChel;
			break;
		}
	}

	AWeapon_Character* CreatedWeapon = Player->World->SpawnActor<AWeapon_Character>(WeaponClass);
	CreatedWeapon->WeaponOwner = Player;
	CreatedWeapon->LeftAmmo = Amount;
	
	FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
	CreatedWeapon->AttachToComponent(Player->WeaponPosition, AttachmentRules);
	
	Player->CurrentWeapons[1]->Destroy();
	Player->CurrentWeapons[1] = CreatedWeapon;

	if (Player->CurrentIndex == 0 && Player->CurrentWeapons[0]->LeftAmmo == 0 || Player->CurrentIndex == 1) {
		Player->SetWeaponToSlot(1);
	}
	else {
		CreatedWeapon->GunMesh->SetVisibility(false);
	}
}