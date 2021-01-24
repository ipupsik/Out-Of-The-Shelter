// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon_Projectile.h"
#include "Chel.h"

AWeapon_Projectile::AWeapon_Projectile()
{

}

float AWeapon_Projectile::GetDamage(AChel* Player)
{
	return Damage / (1 + 0.2 * Player->ShieldsCount) * Player->ArmoryZelieEffect;
}

void AWeapon_Projectile::CallAddMarker()
{
	TArray<AActor*> Temp;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AChel::StaticClass(), Temp);
	for (auto& it : Temp) {
		AChel* Pl = Cast<AChel>(it);
		if (Pl && Pl->Index == IndexOwner) {
			Pl->AddHitMarker();
		}
	}
}