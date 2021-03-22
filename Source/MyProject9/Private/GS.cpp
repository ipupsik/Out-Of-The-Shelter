// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "GS.h" 
#include "Kismet/GameplayStatics.h"
#include "Chel.h"
#include "Engine/TargetPoint.h"
#include "AreaCollision.h"
#include "GM.h"
#include "DezinfectorNasos.h"
#include "WebCamPoint.h"
#include "BP_VentilaciaRubilnick.h"
#include "PromptCollisionArea.h"
#include "CollectableItem.h"
#include "InteractiveCache.h"
#include "CollisionOutlineRubilnici.h"
#include "CollisionOutlineNasos.h"
#include "Details.h"
#include "Weapon_Character.h"

AGS::AGS() {
	PrimaryActorTick.bCanEverTick = true;

	NickNames.Init(FText::FromString(TEXT(" ")), 4);
	WinnersIndex.Init(0, 0);
	WinnersNickNames.Init(FText::FromString(TEXT("")), 0);
	Keys_Transform.Init({}, 0);
	Keys_IsAvaliable.Init(true, 0);
	CacheItems_Stuff_IsAvaliable.Init(true, 0);
	EscapeTime.Init(0, 0);
	AcceptPiedistalAmount = 0;
	AmountOfPlayers = 0;
	AgreedPlayers = 0;
	IsCanalizaciaPlayed = true;
	IsVentilationPlayed = true;
	GeneralLayer = 0;
	AreaAvaliables.Init(false, 3);
	AreaClosed.Init(false, 3);
	Areas.Init(nullptr, 4);

	RespawnPointAvaliable.Init(true, 4);

	IsGameStarted = false;

	CurrentButtonCount = 0;
	IsShelterAvaliable = false;
	IsVentilaciaAvaliable = false;
	IsCanalizaciaAvaliable = false;
	CodeGenerator = -1;
	CurrentCode = 0;
	ButtonPlayAnim = false;
	NumbersOnPanel.Init(nullptr, 0);
	StackOfPointsNum.Init(0, 0);
}

void AGS::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGS, AreaAvaliables);
	DOREPLIFETIME(AGS, AreaClosed);
	DOREPLIFETIME(AGS, CodeGenerator);
	DOREPLIFETIME(AGS, ButtonPlayAnim);
	DOREPLIFETIME(AGS, NumbersOnPanel);
	DOREPLIFETIME(AGS, IsShelterAvaliable);
	DOREPLIFETIME(AGS, IsVentilaciaAvaliable);
	DOREPLIFETIME(AGS, IsCanalizaciaAvaliable);
	DOREPLIFETIME(AGS, IsCanalizaciaPlayed);
	DOREPLIFETIME(AGS, IsVentilationPlayed);
	DOREPLIFETIME(AGS, VentilaciaRubilnickCount);
	DOREPLIFETIME(AGS, MaxVentilaciaRubilnickCount);
	DOREPLIFETIME(AGS, CanalizaciaNasosCount);
	DOREPLIFETIME(AGS, MaxCanalizaciaNasosCount);
}

void AGS::BeginPlay()
{
	Super::BeginPlay();

	if (GetLocalRole() == ROLE_Authority) {
		MaxPlayersCount = GetWorld()->GetGameInstance<UGI>()->MaxPlayersCount;
		for (int i = 0; i < 4; ++i) {
			GetWorld()->SpawnActor<AFinalMenuPawn>(FMP, TransFMP);
		}

		TArray<AActor*>FindAreas;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAreaCollision::StaticClass(), FindAreas);
		for (auto& FindArea : FindAreas) {
			AAreaCollision* TmpArea = Cast<AAreaCollision>(FindArea);
			Areas[TmpArea->AreaType] = Cast<AAreaCollision>(FindArea);
		}
		UE_LOG(LogTemp, Warning, TEXT("%d"), Areas.Num());

		TArray<AActor*>WebCamSpectators;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWebCamPoint::StaticClass(), WebCamSpectators);
		for (int i = 0; i < WebCamSpectators.Num(); ++i)
		{
			WebCams.Add(Cast<AWebCamPoint>(WebCamSpectators[i]));
		}

		TArray<AActor*>VentilaciaRubilnick;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABP_VentilaciaRubilnick::StaticClass(), VentilaciaRubilnick);
		MaxVentilaciaRubilnickCount = VentilaciaRubilnickCount = VentilaciaRubilnick.Num();

		if (MaxPlayersCount <= 3) {
			VentilaciaRubilnickCount -= 2;
			MaxVentilaciaRubilnickCount -= 2;
		}

		TArray<AActor*>CanalizaciaNasos;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADezinfectorNasos::StaticClass(), CanalizaciaNasos);
		MaxCanalizaciaNasosCount = CanalizaciaNasosCount = CanalizaciaNasos.Num();

		//----------------------------Cache Items

		TArray<AActor*>TargetPoints_CacheItems;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AInteractiveCache::StaticClass(), TargetPoints_CacheItems);
		
		for (int i = 0; i < TargetPoints_CacheItems.Num(); ++i)
		{
			CacheItems_Stuff_IsAvaliable.Add(true);
			Caches.Add(Cast<AInteractiveCache>(TargetPoints_CacheItems[i]));
		}

		for (int i = 0; i < 1; ++i) {
			int ArrayIndex = FMath::RandRange(0, CacheItems_Stuff_IsAvaliable.Num() - 1);
			while (!CacheItems_Stuff_IsAvaliable[ArrayIndex])
			{
				ArrayIndex++;
				if (ArrayIndex >= CacheItems_Stuff_IsAvaliable.Num())
					ArrayIndex = 0;
			}
			AActor* NewItem = GetWorld()->SpawnActor<AActor>(KeyShelter);
			FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
			NewItem->AttachToActor(Caches[ArrayIndex], AttachmentRules);
			NewItem->SetActorScale3D(KeyShelterTransform[Caches[ArrayIndex]->CacheIndex].GetScale3D());
			NewItem->AddActorLocalOffset(KeyShelterTransform[Caches[ArrayIndex]->CacheIndex].GetLocation());
			NewItem->AddActorLocalRotation(KeyShelterTransform[Caches[ArrayIndex]->CacheIndex].GetRotation());
			Cast<ACollectableItem>(NewItem)->EnabledArrayIndex = ArrayIndex;
			CacheItems_Stuff_IsAvaliable[ArrayIndex] = false;
		}

		if (MaxPlayersCount == 4) {
			for (int i = 0; i < 1; ++i) {
				int ArrayIndex = FMath::RandRange(0, CacheItems_Stuff_IsAvaliable.Num() - 1);
				while (!CacheItems_Stuff_IsAvaliable[ArrayIndex])
				{
					ArrayIndex++;
					if (ArrayIndex >= CacheItems_Stuff_IsAvaliable.Num())
						ArrayIndex = 0;
				}
				AActor* NewItem = GetWorld()->SpawnActor<AActor>(Boltorez);
				FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
				NewItem->AttachToActor(Caches[ArrayIndex], AttachmentRules);
				NewItem->SetActorScale3D(BoltorezTransform[Caches[ArrayIndex]->CacheIndex].GetScale3D());
				NewItem->AddActorLocalOffset(BoltorezTransform[Caches[ArrayIndex]->CacheIndex].GetLocation());
				NewItem->AddActorLocalRotation(BoltorezTransform[Caches[ArrayIndex]->CacheIndex].GetRotation());
				Cast<ACollectableItem>(NewItem)->EnabledArrayIndex = ArrayIndex;
				CacheItems_Stuff_IsAvaliable[ArrayIndex] = false;
			}
		}
		else
			IsCanalizaciaPlayed = false;


		if (MaxPlayersCount >= 3) {
			for (int i = 0; i < 1; ++i) {
				int ArrayIndex = FMath::RandRange(0, CacheItems_Stuff_IsAvaliable.Num() - 1);
				while (!CacheItems_Stuff_IsAvaliable[ArrayIndex])
				{
					ArrayIndex++;
					if (ArrayIndex >= CacheItems_Stuff_IsAvaliable.Num())
						ArrayIndex = 0;
				}

				AActor* NewItem = GetWorld()->SpawnActor<AActor>(Otvertka);
				FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
				NewItem->AttachToActor(Caches[ArrayIndex], AttachmentRules);
				NewItem->SetActorScale3D(OtvertkaTransform[Caches[ArrayIndex]->CacheIndex].GetScale3D());
				NewItem->AddActorLocalOffset(OtvertkaTransform[Caches[ArrayIndex]->CacheIndex].GetLocation());
				NewItem->AddActorLocalRotation(OtvertkaTransform[Caches[ArrayIndex]->CacheIndex].GetRotation());
				Cast<ACollectableItem>(NewItem)->EnabledArrayIndex = ArrayIndex;
				CacheItems_Stuff_IsAvaliable[ArrayIndex] = false;
			}
		}
		else {
			IsVentilationPlayed = false;
		}

		for (int i = 0; i < 6; ++i) {
			int ArrayIndex = FMath::RandRange(0, CacheItems_Stuff_IsAvaliable.Num() - 1);
			while (!CacheItems_Stuff_IsAvaliable[ArrayIndex])
			{
				ArrayIndex++;
				if (ArrayIndex >= CacheItems_Stuff_IsAvaliable.Num())
					ArrayIndex = 0;
			}
			AActor* NewItem = GetWorld()->SpawnActor<AActor>(HealPacket_class);
			FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
			NewItem->AttachToActor(Caches[ArrayIndex], AttachmentRules);
			NewItem->SetActorScale3D(HealPacketTransform[Caches[ArrayIndex]->CacheIndex].GetScale3D());
			NewItem->AddActorLocalOffset(HealPacketTransform[Caches[ArrayIndex]->CacheIndex].GetLocation());
			NewItem->AddActorLocalRotation(HealPacketTransform[Caches[ArrayIndex]->CacheIndex].GetRotation());
			Cast<ACollectableItem>(NewItem)->EnabledArrayIndex = ArrayIndex;
			CacheItems_Stuff_IsAvaliable[ArrayIndex] = false;
		}

		for (int i = 0; i < 10; ++i) {
			int ArrayIndex = FMath::RandRange(0, CacheItems_Stuff_IsAvaliable.Num() - 1);
			while (!CacheItems_Stuff_IsAvaliable[ArrayIndex])
			{
				ArrayIndex++;
				if (ArrayIndex >= CacheItems_Stuff_IsAvaliable.Num())
					ArrayIndex = 0;
			}
			AActor* NewItem = GetWorld()->SpawnActor<AActor>(Shileds_class);
			FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
			NewItem->AttachToActor(Caches[ArrayIndex], AttachmentRules);
			NewItem->SetActorScale3D(ShiledsTransform[Caches[ArrayIndex]->CacheIndex].GetScale3D());
			NewItem->AddActorLocalOffset(ShiledsTransform[Caches[ArrayIndex]->CacheIndex].GetLocation());
			NewItem->AddActorLocalRotation(ShiledsTransform[Caches[ArrayIndex]->CacheIndex].GetRotation());
			Cast<ACollectableItem>(NewItem)->EnabledArrayIndex = ArrayIndex;
			CacheItems_Stuff_IsAvaliable[ArrayIndex] = false;
		}

		for (int i = 0; i < 4; ++i) {
			int ArrayIndex = FMath::RandRange(0, CacheItems_Stuff_IsAvaliable.Num() - 1);
			while (!CacheItems_Stuff_IsAvaliable[ArrayIndex])
			{
				ArrayIndex++;
				if (ArrayIndex >= CacheItems_Stuff_IsAvaliable.Num())
					ArrayIndex = 0;
			}
			AActor* NewItem = GetWorld()->SpawnActor<AActor>(AmmoBackPack_Class);
			FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
			NewItem->AttachToActor(Caches[ArrayIndex], AttachmentRules);
			NewItem->SetActorScale3D(AmmoBackPackTransform[Caches[ArrayIndex]->CacheIndex].GetScale3D());
			NewItem->AddActorLocalOffset(AmmoBackPackTransform[Caches[ArrayIndex]->CacheIndex].GetLocation());
			NewItem->AddActorLocalRotation(AmmoBackPackTransform[Caches[ArrayIndex]->CacheIndex].GetRotation());
			Cast<ACollectableItem>(NewItem)->EnabledArrayIndex = ArrayIndex;
			CacheItems_Stuff_IsAvaliable[ArrayIndex] = false;
		}

		for (int i = 0; i < 1; ++i) {
			int ArrayIndex = FMath::RandRange(0, CacheItems_Stuff_IsAvaliable.Num() - 1);
			while (!CacheItems_Stuff_IsAvaliable[ArrayIndex])
			{
				ArrayIndex++;
				if (ArrayIndex >= CacheItems_Stuff_IsAvaliable.Num())
					ArrayIndex = 0;
			}
			AActor* NewItem = GetWorld()->SpawnActor<AActor>(ChelDetector_class);
			FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
			NewItem->AttachToActor(Caches[ArrayIndex], AttachmentRules);
			NewItem->SetActorScale3D(ChelDetectorTransform[Caches[ArrayIndex]->CacheIndex].GetScale3D());
			NewItem->AddActorLocalOffset(ChelDetectorTransform[Caches[ArrayIndex]->CacheIndex].GetLocation());
			NewItem->AddActorLocalRotation(ChelDetectorTransform[Caches[ArrayIndex]->CacheIndex].GetRotation());
			Cast<ACollectableItem>(NewItem)->EnabledArrayIndex = ArrayIndex;
			CacheItems_Stuff_IsAvaliable[ArrayIndex] = false;
		}

		for (int i = 0; i < 4; ++i) {
			int ArrayIndex = FMath::RandRange(0, CacheItems_Stuff_IsAvaliable.Num() - 1);
			while (!CacheItems_Stuff_IsAvaliable[ArrayIndex])
			{
				ArrayIndex++;
				if (ArrayIndex >= CacheItems_Stuff_IsAvaliable.Num())
					ArrayIndex = 0;
			}
			AActor* NewItem = GetWorld()->SpawnActor<AActor>(InvisiblePotion_class);
			FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
			NewItem->AttachToActor(Caches[ArrayIndex], AttachmentRules);
			NewItem->SetActorScale3D(ZelieTransform[Caches[ArrayIndex]->CacheIndex].GetScale3D());
			NewItem->AddActorLocalOffset(ZelieTransform[Caches[ArrayIndex]->CacheIndex].GetLocation());
			NewItem->AddActorLocalRotation(ZelieTransform[Caches[ArrayIndex]->CacheIndex].GetRotation());
			Cast<ACollectableItem>(NewItem)->EnabledArrayIndex = ArrayIndex;
			CacheItems_Stuff_IsAvaliable[ArrayIndex] = false;
		}

		for (int i = 0; i < 6; ++i) {
			int ArrayIndex = FMath::RandRange(0, CacheItems_Stuff_IsAvaliable.Num() - 1);
			while (!CacheItems_Stuff_IsAvaliable[ArrayIndex])
			{
				ArrayIndex++;
				if (ArrayIndex >= CacheItems_Stuff_IsAvaliable.Num())
					ArrayIndex = 0;
			}
			AActor* NewItem = GetWorld()->SpawnActor<AActor>(AntiRadZelie_class);
			FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
			NewItem->AttachToActor(Caches[ArrayIndex], AttachmentRules);
			NewItem->SetActorScale3D(ZelieTransform[Caches[ArrayIndex]->CacheIndex].GetScale3D());
			NewItem->AddActorLocalOffset(ZelieTransform[Caches[ArrayIndex]->CacheIndex].GetLocation());
			NewItem->AddActorLocalRotation(ZelieTransform[Caches[ArrayIndex]->CacheIndex].GetRotation());
			Cast<ACollectableItem>(NewItem)->EnabledArrayIndex = ArrayIndex;
			CacheItems_Stuff_IsAvaliable[ArrayIndex] = false;
		}

		for (int i = 0; i < 6; ++i) {
			int ArrayIndex = FMath::RandRange(0, CacheItems_Stuff_IsAvaliable.Num() - 1);
			while (!CacheItems_Stuff_IsAvaliable[ArrayIndex])
			{
				ArrayIndex++;
				if (ArrayIndex >= CacheItems_Stuff_IsAvaliable.Num())
					ArrayIndex = 0;
			}
			AActor* NewItem = GetWorld()->SpawnActor<AActor>(ArmoryZelie_class);
			FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
			NewItem->AttachToActor(Caches[ArrayIndex], AttachmentRules);
			NewItem->SetActorScale3D(ZelieTransform[Caches[ArrayIndex]->CacheIndex].GetScale3D());
			NewItem->AddActorLocalOffset(ZelieTransform[Caches[ArrayIndex]->CacheIndex].GetLocation());
			NewItem->AddActorLocalRotation(ZelieTransform[Caches[ArrayIndex]->CacheIndex].GetRotation());
			Cast<ACollectableItem>(NewItem)->EnabledArrayIndex = ArrayIndex;
			CacheItems_Stuff_IsAvaliable[ArrayIndex] = false;
		}

		for (int i = 0; i < 3; ++i) {
			int ArrayIndex = FMath::RandRange(0, CacheItems_Stuff_IsAvaliable.Num() - 1);
			while (!CacheItems_Stuff_IsAvaliable[ArrayIndex])
			{
				ArrayIndex++;
				if (ArrayIndex >= CacheItems_Stuff_IsAvaliable.Num())
					ArrayIndex = 0;
			}
			AWeapon_Level* NewItem = GetWorld()->SpawnActor<AWeapon_Level>(Axe_Class);
			FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
			NewItem->AttachToActor(Caches[ArrayIndex], AttachmentRules);
			NewItem->SetActorScale3D(AxeTransform[Caches[ArrayIndex]->CacheIndex].GetScale3D());
			NewItem->AddActorLocalOffset(AxeTransform[Caches[ArrayIndex]->CacheIndex].GetLocation());
			NewItem->AddActorLocalRotation(AxeTransform[Caches[ArrayIndex]->CacheIndex].GetRotation());
			NewItem->EnabledArrayIndex = ArrayIndex;
			CacheItems_Stuff_IsAvaliable[ArrayIndex] = false;
			NewItem->Amount = 1;
			NewItem->DisableComponentsSimulatePhysics();
		}

		for (int i = 0; i < 3; ++i) {
			int ArrayIndex = FMath::RandRange(0, CacheItems_Stuff_IsAvaliable.Num() - 1);
			while (!CacheItems_Stuff_IsAvaliable[ArrayIndex])
			{
				ArrayIndex++;
				if (ArrayIndex >= CacheItems_Stuff_IsAvaliable.Num())
					ArrayIndex = 0;
			}
			AWeapon_Level* NewItem = GetWorld()->SpawnActor<AWeapon_Level>(Bottle_Class);
			FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
			NewItem->AttachToActor(Caches[ArrayIndex], AttachmentRules);
			NewItem->SetActorScale3D(BottleTransform[Caches[ArrayIndex]->CacheIndex].GetScale3D());
			NewItem->AddActorLocalOffset(BottleTransform[Caches[ArrayIndex]->CacheIndex].GetLocation());
			NewItem->AddActorLocalRotation(BottleTransform[Caches[ArrayIndex]->CacheIndex].GetRotation());
			NewItem->EnabledArrayIndex = ArrayIndex;
			CacheItems_Stuff_IsAvaliable[ArrayIndex] = false;
			NewItem->Amount = 1 + FMath::RandRange(0, 4);
		}

		for (int i = 0; i < 3; ++i) {
			int ArrayIndex = FMath::RandRange(0, CacheItems_Stuff_IsAvaliable.Num() - 1);
			while (!CacheItems_Stuff_IsAvaliable[ArrayIndex])
			{
				ArrayIndex++;
				if (ArrayIndex >= CacheItems_Stuff_IsAvaliable.Num())
					ArrayIndex = 0;
			}
			AWeapon_Level* NewItem = GetWorld()->SpawnActor<AWeapon_Level>(Knife_Class);
			FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
			NewItem->AttachToActor(Caches[ArrayIndex], AttachmentRules);
			NewItem->SetActorScale3D(KnifeTransform[Caches[ArrayIndex]->CacheIndex].GetScale3D());
			NewItem->AddActorLocalOffset(KnifeTransform[Caches[ArrayIndex]->CacheIndex].GetLocation());
			NewItem->AddActorLocalRotation(KnifeTransform[Caches[ArrayIndex]->CacheIndex].GetRotation());
			NewItem->EnabledArrayIndex = ArrayIndex;
			CacheItems_Stuff_IsAvaliable[ArrayIndex] = false;
			NewItem->Amount = 1 + FMath::RandRange(0, 3);
			NewItem->DisableComponentsSimulatePhysics();
		}

		for (int i = 0; i < 6; ++i) {
			int ArrayIndex = FMath::RandRange(0, CacheItems_Stuff_IsAvaliable.Num() - 1);
			while (!CacheItems_Stuff_IsAvaliable[ArrayIndex])
			{
				ArrayIndex++;
				if (ArrayIndex >= CacheItems_Stuff_IsAvaliable.Num())
					ArrayIndex = 0;
			}
			AActor* NewItem = GetWorld()->SpawnActor<AActor>(ProjectileZelie_class);
			FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
			NewItem->AttachToActor(Caches[ArrayIndex], AttachmentRules);
			NewItem->SetActorScale3D(ArmoryZelieTransform[Caches[ArrayIndex]->CacheIndex].GetScale3D());
			NewItem->AddActorLocalOffset(ArmoryZelieTransform[Caches[ArrayIndex]->CacheIndex].GetLocation());
			NewItem->AddActorLocalRotation(ArmoryZelieTransform[Caches[ArrayIndex]->CacheIndex].GetRotation());
			Cast<ACollectableItem>(NewItem)->EnabledArrayIndex = ArrayIndex;
			CacheItems_Stuff_IsAvaliable[ArrayIndex] = false;
		}

		for (int i = 0; i < 1; ++i) {
			int ArrayIndex = FMath::RandRange(0, CacheItems_Stuff_IsAvaliable.Num() - 1);
			while (!CacheItems_Stuff_IsAvaliable[ArrayIndex])
			{
				ArrayIndex++;
				if (ArrayIndex >= CacheItems_Stuff_IsAvaliable.Num())
					ArrayIndex = 0;
			}
			AActor* NewItem = GetWorld()->SpawnActor<AActor>(RentgenGlass_class);
			FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
			NewItem->AttachToActor(Caches[ArrayIndex], AttachmentRules);
			NewItem->SetActorScale3D(RentgenGlassTransform[Caches[ArrayIndex]->CacheIndex].GetScale3D());
			NewItem->AddActorLocalOffset(RentgenGlassTransform[Caches[ArrayIndex]->CacheIndex].GetLocation());
			NewItem->AddActorLocalRotation(RentgenGlassTransform[Caches[ArrayIndex]->CacheIndex].GetRotation());
			Cast<ACollectableItem>(NewItem)->EnabledArrayIndex = ArrayIndex;
			CacheItems_Stuff_IsAvaliable[ArrayIndex] = false;
		}

		for (int i = 0; i < 5; ++i) {
			int ArrayIndex = FMath::RandRange(0, CacheItems_Stuff_IsAvaliable.Num() - 1);
			while (!CacheItems_Stuff_IsAvaliable[ArrayIndex])
			{
				ArrayIndex++;
				if (ArrayIndex >= CacheItems_Stuff_IsAvaliable.Num())
					ArrayIndex = 0;
			}
			AActor* NewItem = GetWorld()->SpawnActor<AActor>(ExtraDetails_class);
			FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
			NewItem->AttachToActor(Caches[ArrayIndex], AttachmentRules);
			NewItem->SetActorScale3D(ExtraDetailsTransform[Caches[ArrayIndex]->CacheIndex].GetScale3D());
			NewItem->AddActorLocalOffset(ExtraDetailsTransform[Caches[ArrayIndex]->CacheIndex].GetLocation());
			NewItem->AddActorLocalRotation(ExtraDetailsTransform[Caches[ArrayIndex]->CacheIndex].GetRotation());
			Cast<ACollectableItem>(NewItem)->EnabledArrayIndex = ArrayIndex;
			CacheItems_Stuff_IsAvaliable[ArrayIndex] = false;
		}

		for (int i = 0; i < MaxPlayersCount; ++i) {
			int ArrayIndex = FMath::RandRange(0, CacheItems_Stuff_IsAvaliable.Num() - 1);
			while (!CacheItems_Stuff_IsAvaliable[ArrayIndex])
			{
				ArrayIndex++;
				if (ArrayIndex >= CacheItems_Stuff_IsAvaliable.Num())
					ArrayIndex = 0;
			}
			AActor* NewItem = GetWorld()->SpawnActor<AActor>(SpecialWeapon_class);
			FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
			NewItem->AttachToActor(Caches[ArrayIndex], AttachmentRules);
			NewItem->SetActorScale3D(SpecialWeaponTransform[Caches[ArrayIndex]->CacheIndex].GetScale3D());
			NewItem->AddActorLocalOffset(SpecialWeaponTransform[Caches[ArrayIndex]->CacheIndex].GetLocation());
			NewItem->AddActorLocalRotation(SpecialWeaponTransform[Caches[ArrayIndex]->CacheIndex].GetRotation());
			Cast<ACollectableItem>(NewItem)->EnabledArrayIndex = ArrayIndex;
			CacheItems_Stuff_IsAvaliable[ArrayIndex] = false;
		}

		for (int i = 0; i < MaxPlayersCount * 2; ++i) {
			int ArrayIndex = FMath::RandRange(0, CacheItems_Stuff_IsAvaliable.Num() - 1);
			while (!CacheItems_Stuff_IsAvaliable[ArrayIndex])
			{
				ArrayIndex++;
				if (ArrayIndex >= CacheItems_Stuff_IsAvaliable.Num())
					ArrayIndex = 0;
			}
			AActor* NewItem = GetWorld()->SpawnActor<AActor>(BubenCache_class);
			FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
			NewItem->AttachToActor(Caches[ArrayIndex], AttachmentRules);
			NewItem->SetActorScale3D(BubenCacheTransform[Caches[ArrayIndex]->CacheIndex].GetScale3D());
			NewItem->AddActorLocalOffset(BubenCacheTransform[Caches[ArrayIndex]->CacheIndex].GetLocation());
			NewItem->AddActorLocalRotation(BubenCacheTransform[Caches[ArrayIndex]->CacheIndex].GetRotation());
			Cast<ACollectableItem>(NewItem)->EnabledArrayIndex = ArrayIndex;
			CacheItems_Stuff_IsAvaliable[ArrayIndex] = false;
		}

		for (int i = 0; i < MaxPlayersCount * 2; ++i) {
			int ArrayIndex = FMath::RandRange(0, CacheItems_Stuff_IsAvaliable.Num() - 1);
			while (!CacheItems_Stuff_IsAvaliable[ArrayIndex])
			{
				ArrayIndex++;
				if (ArrayIndex >= CacheItems_Stuff_IsAvaliable.Num())
					ArrayIndex = 0;
			}
			AActor* NewItem = GetWorld()->SpawnActor<AActor>(BubenDetail_class);
			FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
			NewItem->AttachToActor(Caches[ArrayIndex], AttachmentRules);
			NewItem->SetActorScale3D(BubenDetailTransform[Caches[ArrayIndex]->CacheIndex].GetScale3D());
			NewItem->AddActorLocalOffset(BubenDetailTransform[Caches[ArrayIndex]->CacheIndex].GetLocation());
			NewItem->AddActorLocalRotation(BubenDetailTransform[Caches[ArrayIndex]->CacheIndex].GetRotation());
			Cast<ACollectableItem>(NewItem)->EnabledArrayIndex = ArrayIndex;
			CacheItems_Stuff_IsAvaliable[ArrayIndex] = false;
		}

		//------------------------------------Cache Keys
		TArray<AActor*>TargetPoints_CacheKey;
		UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), ATargetPoint::StaticClass(), FName("CacheKeys"), TargetPoints_CacheKey);

		for (int i = 0; i < TargetPoints_CacheKey.Num(); ++i)
		{
			Keys_Transform.Add(TargetPoints_CacheKey[i]->GetActorTransform());
			Keys_IsAvaliable.Add(true);
		}

		for (int Keys = 0; Keys < 3; ++Keys)
		{
			for (int i = 0; i < 14; ++i)
			{
				int ArrayIndex = FMath::RandRange(0, Keys_IsAvaliable.Num() - 1);
				while (!Keys_IsAvaliable[ArrayIndex])
				{
					ArrayIndex++;
					if (ArrayIndex >= CacheItems_Stuff_IsAvaliable.Num())
						ArrayIndex = 0;
				}

				AActor* NewItem = nullptr;
				if (Keys == 0)
				{
					NewItem = GetWorld()->SpawnActor<AActor>(BronzeKey, Keys_Transform[ArrayIndex]);
				}
				else if (Keys == 1)
				{
					NewItem = GetWorld()->SpawnActor<AActor>(SilverKey, Keys_Transform[ArrayIndex]);
				}
				else if (Keys == 2)
				{
					NewItem = GetWorld()->SpawnActor<AActor>(GoldKey, Keys_Transform[ArrayIndex]);
				}
				if (NewItem) {
					Cast<ACollectableItem>(NewItem)->EnabledArrayIndex = ArrayIndex;
					Keys_IsAvaliable[ArrayIndex] = false;
				}
			}
		}
		// Details
		TArray<AActor*>TargetPoints_Details;
		UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), ATargetPoint::StaticClass(), FName("Details"), TargetPoints_Details);

		for (int i = 0; i < TargetPoints_Details.Num(); ++i)
		{
			Details_Transform.Add(TargetPoints_Details[i]->GetActorTransform());
			Details_IsAvaliable.Add(true);
		}

		for (int Det = 0; Det < 35; ++Det)
		{
			int ArrayIndex = FMath::RandRange(0, Details_IsAvaliable.Num() - 1);
			while (!Details_IsAvaliable[ArrayIndex])
			{
				ArrayIndex++;
				if (ArrayIndex >= Details_IsAvaliable.Num())
					ArrayIndex = 0;
			}

			AActor* NewItem = GetWorld()->SpawnActor<AActor>(Details_class, Details_Transform[ArrayIndex]);
			Cast<ACollectableItem>(NewItem)->EnabledArrayIndex = ArrayIndex;
			Details_IsAvaliable[ArrayIndex] = false;
		}
		//Details

		TArray<AActor*>TargetPoints_TerminalLamp;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATerminalLight::StaticClass(), TargetPoints_TerminalLamp);
		if (TargetPoints_TerminalLamp.Num() > 0)
			LampObj = Cast<ATerminalLight>(TargetPoints_TerminalLamp[0]);
	}
}

void AGS::GameBegin() {
	IsGameStarted = true;
	TArray<AActor*> Players;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AChel::StaticClass(), Players);
	for (auto& Player : Players) {
		UE_LOG(LogTemp, Warning, TEXT("SpawnAnimationGS"));
		AChel* Chel = Cast<AChel>(Player);
		Chel->PlaySpawnAnimationSleep();
	}

	FTimerHandle FuzeTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(FuzeTimerHandle, this, &AGS::SpawnPlayers, 2, false);
}

void AGS::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	CurrentTime += DeltaSeconds;
}

void AGS::SpawnPlayers()
{
	UE_LOG(LogTemp, Warning, TEXT("SpawnPlayers"));
	TArray<AActor*> SpawnPoints;
	TArray<AActor*> Players;

	CurrentTime = 0.0f;

	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), ATargetPoint::StaticClass(), TEXT("spawn"), SpawnPoints);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AChel::StaticClass(), Players);
	for (int i = 0; i < Players.Num(); i++) {
		AChel* Player = Cast<AChel>(Players[i]);
		Player->SpawnPlayer();
	}

	FTimerHandle FuzeTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(FuzeTimerHandle, this, &AGS::CreateGasOnFloor, RandomEventDuration, false);
}

void AGS::ResetGame() {
	Cast<AGM>(UGameplayStatics::GetGameMode(GetWorld()))->Respawn();
}

void AGS::EventSpawnNote() {
	CodeGenerator = (1 + FMath::RandRange(0, 8)) * 10000 + FMath::RandRange(0, 9) * 1000 + FMath::RandRange(0, 9) * 100 + FMath::RandRange(0, 9) * 10 + FMath::RandRange(0, 9);
	TArray<AActor*> GettingTagActors;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), ATargetPoint::StaticClass(), "NoteSpawn", GettingTagActors);
	GetWorld()->SpawnActor<ACodeNote_New>(CodeNoteClass, GettingTagActors[FMath::RandRange(0, GettingTagActors.Num() - 1)]->GetTransform());
	UE_LOG(LogTemp, Warning, TEXT("Note was spawned"));
}

void AGS::AddNumToTerminal(int32 Number) {
	FTransform Trans;
	Trans.SetLocation(FVector(TransformOfFirstNum.GetLocation().X + 11 * NumbersOnPanel.Num(), TransformOfFirstNum.GetLocation().Y, TransformOfFirstNum.GetLocation().Z));
	Trans.SetRotation(TransformOfFirstNum.GetRotation());
	ATerminalNumber* Num = GetWorld()->SpawnActorDeferred<ATerminalNumber>(NumberTerminalClass, Trans);
	if (Num != nullptr)
	{
		Num->NumberType = Number;
		UGameplayStatics::FinishSpawningActor(Num, Trans);
		Num->SetActorScale3D(TransformOfFirstNum.GetScale3D());
		if (Num != nullptr)
			NumbersOnPanel.Add(Num);
		else
			UE_LOG(LogTemp, Warning, TEXT("Govno2"))
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Govno1"));
	ClickOnButtonTerminal(LampObj->GetActorLocation());
}

void AGS::DeleteLastNumber() {
	ClickOnButtonTerminal(LampObj->GetActorLocation());
	NumbersOnPanel[NumbersOnPanel.Num() - 1]->Destroy();
	NumbersOnPanel.Pop();
}

void AGS::CheckCode(int Index) {
	CurrentCode = 0;
	if (NumbersOnPanel.Num() == 5) {
		CurrentCode = NumbersOnPanel[0]->NumberType * 10000 + NumbersOnPanel[1]->NumberType * 1000 + NumbersOnPanel[2]->NumberType * 100 + NumbersOnPanel[3]->NumberType * 10 + NumbersOnPanel[4]->NumberType;
		if (CurrentCode == CodeGenerator) {

			TArray<AActor*> GettingChelix;
			IsShelterAvaliable = false;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), AChel::StaticClass(), GettingChelix);
			for (auto& it : GettingChelix) 
			{
				Cast<AChel>(it)->HideNoteWidget();
			}
			
			TArray<AActor*> Generator;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGeneratorArea::StaticClass(), Generator);

			if (Generator[0]) {
				AGeneratorArea* GeneratorAreaTmp = Cast<AGeneratorArea>(Generator[0]);
				for (auto& it : GeneratorAreaTmp->PromtCollisionTerminal)
				{
					it->bISAvaliable = false;
				}
				TArray<AActor*>ChelixZero;
				GeneratorAreaTmp->ShelterCollision[0]->Collision->GetOverlappingActors(ChelixZero, AChel::StaticClass());
				for (auto& it : ChelixZero)
				{
					Cast<AChel>(it)->ShowUIAfterTerminalAndGenerator(1, false);
				}

				TArray<AActor*>ChelixOne;
				GeneratorAreaTmp->ShelterCollision[1]->Collision->GetOverlappingActors(ChelixOne, AChel::StaticClass());
				for (auto& it : ChelixOne)
				{
					Cast<AChel>(it)->ShowUIAfterTerminalAndGenerator(3, false);
				}
				GeneratorAreaTmp->ChangeSoundAmbientToNotWorking();
			}

			TArray<AActor*> GettingCodeNote;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACodeNote_New::StaticClass(), GettingCodeNote);
			for (auto& it : GettingCodeNote)
			{
				Cast<ACodeNote_New>(it)->Destroy();
			}
			PlayGoodSoundTerminal(LampObj->GetActorLocation());

			FTimerHandle FuzeTimerHandle;
			GetWorld()->GetTimerManager().SetTimer(FuzeTimerHandle, this, &AGS::RefreshGenerator, 20, false);

			for (auto& it : GettingChelix)
			{
				AChel* temp = Cast<AChel>(it);
				if (temp->Index == Index)
				{
					temp->ShowRandomItem();
					break;
				}
			}

			LampObj->ChangeMaterialLamp(2);

			for (auto& it : NumbersOnPanel)
			{
				it->Destroy();
			}
			NumbersOnPanel.Empty();

			FTimerHandle FuzeTimerHandle2;
			GetWorld()->GetTimerManager().SetTimer(FuzeTimerHandle2, this, &AGS::ChangeLamp_Neutral, 2, false);

			return;
		}
	}

	for (auto& it : NumbersOnPanel)
	{
		it->Destroy();
	}
	NumbersOnPanel.Empty();

	PlayBadSoundTerminal(LampObj->GetActorLocation());

	LampObj->ChangeMaterialLamp(1);

	FTimerHandle FuzeTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(FuzeTimerHandle, this, &AGS::ChangeLamp_Neutral, 2, false);

	TArray<AActor*> GettingChelix;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AChel::StaticClass(), GettingChelix);
	for (auto& it : GettingChelix)
	{
		AChel* temp = Cast<AChel>(it);
		if (temp->Index == Index) {
			temp->OutlineBad_Server();
			return;
		}
	}
}

void AGS::ChangeLamp_Neutral()
{
	LampObj->ChangeMaterialLamp(0);
}

void AGS::RefreshGenerator()
{
	TArray<AActor*> temp;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APromptCollisionArea::StaticClass(), temp);
	for (auto& it : temp) {
		APromptCollisionArea* CurAreaPromt = Cast<APromptCollisionArea>(it);
		if (CurAreaPromt)
		{
			if(CurAreaPromt->TypePromptCollision == 1) 
			{
				CurAreaPromt->bISAvaliable = true;
				CurAreaPromt->SettingAvaliableTrue();
			}			
		}
	}

	TArray<AActor*> Generator;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGeneratorArea::StaticClass(), Generator);

	AGeneratorArea* FindGenerator = Cast<AGeneratorArea>(Generator[0]);
	if (FindGenerator) {
		FindGenerator->RefreshGenerator();
	}

}


void AGS::CreateGasOnFloor() {
	if (IsGameStarted) { //если в игре
		FName GasAreaParticleTag = "";
		FName GasAreaDamageTag = "";
		int32 Floor = FMath::RandRange(0, 3);
		switch (Floor) {
		case 0:
			GasAreaParticleTag = GasAreaParticleTag_1;
			GasAreaDamageTag = GasAreaDamageTag_1;
			break;
		case 1:
			GasAreaParticleTag = GasAreaParticleTag_2;
			GasAreaDamageTag = GasAreaDamageTag_2;
			break;
		case 2:
			GasAreaParticleTag = GasAreaParticleTag_3;
			GasAreaDamageTag = GasAreaDamageTag_3;
			break;
		case 3:
			GasAreaParticleTag = GasAreaParticleTag_4;
			GasAreaDamageTag = GasAreaDamageTag_4;
			break;
		}

		TArray<AActor*> PartSystem_Targets;
		UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), ATargetPoint::StaticClass(), GasAreaParticleTag, PartSystem_Targets);

		for (auto& it : PartSystem_Targets)
		{
			AParticleGasRandomEvent* PSActor = GetWorld()->SpawnActor<AParticleGasRandomEvent>(ParticleGas_Class, it->GetActorTransform());
			PlaySoundGas(it->GetActorLocation());
		}

		TArray<AActor*> DamageArea_Targets;
		UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), ATargetPoint::StaticClass(), GasAreaDamageTag, DamageArea_Targets);

		for (auto& it : DamageArea_Targets)
		{
			ADamageAreaRandomEvent* DamageActor = GetWorld()->SpawnActor<ADamageAreaRandomEvent>(DamageAreaRandom_Class, it->GetActorTransform());
		}

		TArray<AActor*> Chls;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AChel::StaticClass(), Chls);
		for (auto& it : Chls) {
			AChel* Plr = Cast<AChel>(it);
			if (Plr) {
				Plr->AddMessageRandomEvent(Floor);
			}
		}

		FTimerHandle FuzeTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(FuzeTimerHandle, this, &AGS::RemoveGasFromFloor, 21, false);
	}
}

void AGS::RemoveGasFromFloor() {
	TArray<AActor*> PS_Targets;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AParticleGasRandomEvent::StaticClass(), PS_Targets);

	for (auto& it : PS_Targets)
	{
		if (Cast<AParticleGasRandomEvent>(it))
		{
			it->Destroy();
		}
	}

	TArray<AActor*> DamageArea_Targets;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADamageAreaRandomEvent::StaticClass(), DamageArea_Targets);

	for (auto& it : DamageArea_Targets)
	{
		if (Cast<ADamageAreaRandomEvent>(it))
		{
			it->Destroy();
		}
	}

	FTimerHandle FuzeTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(FuzeTimerHandle, this, &AGS::CreateGasOnFloor, RandomEventDuration, false);
}

void AGS::OffCollisionRubilnici_Implementation() {
	TArray<AActor*> CollisionOutlineRubilnic;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACollisionOutlineRubilnici::StaticClass(), CollisionOutlineRubilnic);
	ACollisionOutlineRubilnici* CurColisionRubilnic = Cast<ACollisionOutlineRubilnici>(CollisionOutlineRubilnic[0]);
	if (CurColisionRubilnic) {
		CurColisionRubilnic->IsEnabled = false;
	}
	if (GetLocalRole() == ROLE_Authority) {
		TArray<AActor*> OvPlayers;
		CurColisionRubilnic->GetOverlappingActors(OvPlayers);
		for (auto& it : OvPlayers) {
			AChel* CurOverlapPlayer = Cast<AChel>(it);
			if (CurOverlapPlayer) {
				CurOverlapPlayer->EventRubilnicCollisionOff_Client();
			}
		}
	}
}

void AGS::OffCollisionNasosi_Implementation() {
	TArray<AActor*> CollisionOutlineNasosi;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACollisionOutlineNasos::StaticClass(), CollisionOutlineNasosi);
	ACollisionOutlineNasos* CurColisionNasos = Cast<ACollisionOutlineNasos>(CollisionOutlineNasosi[0]);
	if (CurColisionNasos) {
		CurColisionNasos->IsEnabled = false;
	}
	if (GetLocalRole() == ROLE_Authority) {
		TArray<AActor*> OvPlayers;
		CurColisionNasos->GetOverlappingActors(OvPlayers);
		for (auto& it : OvPlayers) {
			AChel* CurOverlapPlayer = Cast<AChel>(it);
			if (CurOverlapPlayer) {
				CurOverlapPlayer->EventNasosCollisionOff_Client();
			}
		}
	}
}