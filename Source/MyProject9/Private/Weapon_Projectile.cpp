// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon_Projectile.h"
#include "Chel.h"
#include "ConsumableAbility_Invisible.h"

AWeapon_Projectile::AWeapon_Projectile()
{

}

float AWeapon_Projectile::GetDamage(AChel* Player)
{
	if (Player->IsNowInvisible)
	{
		Player->ReverceInvisibleEverywhere();
		Player->LastInvisibleAbilityObj->DestroyNonNativeProperties();
		Player->World->GetTimerManager().ClearTimer(Player->TimerHandleInvisible);
		Player->IsNowInvisible = false;
	}
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