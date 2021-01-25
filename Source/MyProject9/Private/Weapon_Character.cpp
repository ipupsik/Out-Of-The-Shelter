// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon_Character.h"
#include "Chel.h"
#include "Weapon_Level.h"
#include "Weapon_Projectile.h"
// Sets default values
AWeapon_Character::AWeapon_Character()
{
	GunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunMesh"));
	GunMesh->SetupAttachment(RootComponent);
}

void AWeapon_Character::SpawnProjectile()
{
	FVector Locat;
	FTransform Trsfrm;
	
	Trsfrm.SetLocation(FVector(WeaponOwner->GetActorLocation().X, WeaponOwner->GetActorLocation().Y, GunMesh->GetComponentLocation().Z));
	Trsfrm.SetRotation(FQuat(FRotator(WeaponOwner->Scene->GetComponentRotation()) + RotationProjectile));
	Trsfrm.SetScale3D(FVector(1.0f, 1.0f, 1.0f));
	AWeapon_Projectile* DroppedItm = WeaponOwner->World->SpawnActorDeferred<AWeapon_Projectile>(WeaponProjectileClass, Trsfrm);
	if (DroppedItm) {
		DroppedItm->IndexOwner = WeaponOwner->Index;
		DroppedItm->Damage *= WeaponOwner->ProjectileDamageEffect * (1 + 0.1f * WeaponOwner->StoneDamageBuffCount);
		UGameplayStatics::FinishSpawningActor(DroppedItm, Trsfrm);
	}
}

void AWeapon_Character::DropItem_Implementation()
{
	
	FTransform Trsfrm;
	Trsfrm.SetLocation(WeaponOwner->DamageCollision->GetComponentLocation());
	Trsfrm.SetRotation(FQuat(FRotator(WeaponOwner->DamageCollision->GetComponentRotation()) + RotationDroppedItem));
	Trsfrm.SetScale3D(FVector(1.0f, 1.0f, 1.0f));
	AWeapon_Level* DroppedItm = WeaponOwner->World->SpawnActor<AWeapon_Level>(WeaponLevelClass, Trsfrm);
	DroppedItm->Amount = LeftAmmo;
	DroppedItm->Mesh->SetPhysicsLinearVelocity(FVector(WeaponOwner->Scene->GetForwardVector() * 200.f));
}

void AWeapon_Character::Throw() { //גûחûגאועסÿ ס סונגונא
	if (LeftAmmo > 0) {
		LeftAmmo -= 1;
		WeaponOwner->ChangeAmmoClients(LeftAmmo, WeaponOwner->CurrentIndex);
		WeaponOwner->StartAnimInCurSlot();
	}
}

void AWeapon_Character::AnimationThrow_Finished() {
	SpawnProjectile();
	if (WeaponOwner->GetLocalRole() == ROLE_Authority) {
		if (LeftAmmo == 0) {
			WeaponOwner->ClearWeaponInfoClient();
			WeaponOwner->StartAnimInCurSlotReverse(false);
		}
		else {

			UE_LOG(LogTemp, Warning, TEXT("I am Refreshing Widgets"));
			WeaponOwner->RefreshWidgetAmmoOwningClient(LeftAmmo, MaxAmmo, WeaponOwner->CurrentIndex);
			WeaponOwner->StartAnimInCurSlotReverse(true);
		}
	}
}

void AWeapon_Character::AnimationThrowReverse_Finished() {
	if (WeaponOwner->IsPlayerOwner && LeftAmmo > 0) {
		WeaponOwner->CanFireWeapon = true;
	}
}