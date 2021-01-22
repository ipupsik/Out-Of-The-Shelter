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

AGS::AGS() {
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

	GeneralLayer = 0;
	AreaAvaliables.Init(false, 3);
	AreaClosed.Init(false, 3);
	Areas.Init(nullptr, 4);

	IsGameStarted = false;

	CurrentButtonCount = 0;
	IsShelterAvaliable = false;
	IsVentilaciaAvaliable = false;
	IsCanalizaciaAvaliable = false;
	CodeGenerator = -1;
	CurrentCode = 0;
	ButtonPlayAnim = false;
	NumbersOnPanel.Init(nullptr, 0);
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
}

void AGS::BeginPlay()
{
	Super::BeginPlay();

	if (GetLocalRole() == ROLE_Authority) {
		//Спавним FinalMenuPawn
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
			for (int j = 0; j < WebCamSpectators.Num() - 1 - i; ++j)
			{
				if (Cast<AWebCamPoint>(WebCamSpectators[j])->Index > Cast<AWebCamPoint>(WebCamSpectators[j + 1])->Index)
				{
					Swap<AActor*>(WebCamSpectators[j], WebCamSpectators[j + 1]);
				}
			}
		}
		for (int i = 0; i < WebCamSpectators.Num(); ++i)
		{
			UE_LOG(LogTemp, Warning, TEXT("Index - %d"), Cast<AWebCamPoint>(WebCamSpectators[i])->Index);
			WebCams.Add(Cast<AWebCamPoint>(WebCamSpectators[i]));
			WebCams[i]->is_Enabled = true;
		}

		TArray<AActor*>VentilaciaRubilnick;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABP_VentilaciaRubilnick::StaticClass(), VentilaciaRubilnick);
		VentilaciaRubilnickCount = VentilaciaRubilnick.Num();

		TArray<AActor*>CanalizaciaNasos;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADezinfectorNasos::StaticClass(), CanalizaciaNasos);
		CanalizaciaNasosCount = CanalizaciaNasos.Num();

		//----------------------------Cache Items

		TArray<AActor*>TargetPoints_CacheItems;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AInteractiveCache::StaticClass(), TargetPoints_CacheItems);
		
		for (int i = 0; i < TargetPoints_CacheItems.Num(); ++i)
		{
			CacheItems_Stuff_IsAvaliable.Add(true);
			Caches.Add(Cast<AInteractiveCache>(TargetPoints_CacheItems[i]));
		}

		for (int i = 0; i < 1; ++i) {
			int ArrayIndex = FMath::Rand() % CacheItems_Stuff_IsAvaliable.Num();
			while (!CacheItems_Stuff_IsAvaliable[ArrayIndex])
			{
				ArrayIndex = FMath::Rand() % CacheItems_Stuff_IsAvaliable.Num();
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
				int ArrayIndex = FMath::Rand() % CacheItems_Stuff_IsAvaliable.Num();
				while (!CacheItems_Stuff_IsAvaliable[ArrayIndex])
				{
					ArrayIndex = FMath::Rand() % CacheItems_Stuff_IsAvaliable.Num();
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

		if (MaxPlayersCount >= 3) {
			for (int i = 0; i < 1; ++i) {
				int ArrayIndex = FMath::Rand() % CacheItems_Stuff_IsAvaliable.Num();
				while (!CacheItems_Stuff_IsAvaliable[ArrayIndex])
				{
					ArrayIndex = FMath::Rand() % CacheItems_Stuff_IsAvaliable.Num();
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

		for (int i = 0; i < 6; ++i) {
			int ArrayIndex = FMath::Rand() % CacheItems_Stuff_IsAvaliable.Num();
			while (!CacheItems_Stuff_IsAvaliable[ArrayIndex])
			{
				ArrayIndex = FMath::Rand() % CacheItems_Stuff_IsAvaliable.Num();
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

		for (int i = 0; i < 2; ++i) {
			int ArrayIndex = FMath::Rand() % CacheItems_Stuff_IsAvaliable.Num();
			while (!CacheItems_Stuff_IsAvaliable[ArrayIndex])
			{
				ArrayIndex = FMath::Rand() % CacheItems_Stuff_IsAvaliable.Num();
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
			for (int i = 0; i < COUNT_CacheKey; ++i)
			{
				int ArrayIndex = FMath::Rand() % Keys_IsAvaliable.Num();
				while (!Keys_IsAvaliable[ArrayIndex])
				{
					ArrayIndex = FMath::Rand() % Keys_IsAvaliable.Num();
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

		Player->PlaySpawnAnimationAwake();
		Player->SetActorLocation(SpawnPoints[i]->GetActorLocation());
		//Player->ShowStoneMulticast();
		Player->Ammo = Player->MaxAmmoCount;
		Player->IsInGame = true;
		Player->Health = 0;
	}
}

void AGS::ResetGame() {
	TArray<AActor*>Stuff;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AInteractiveItem::StaticClass(), Stuff);

	for (auto Obj : Stuff)
		Obj->Destroy();

	NickNames.Init(FText::FromString(TEXT(" ")), 4);

	EscapeTime.Init(0, 0);
	AcceptPiedistalAmount = 0;
	AmountOfPlayers = 0;
	AgreedPlayers = 0;

	GeneralLayer = 0;
	AreaAvaliables.Init(false, 3);
	AreaClosed.Init(false, 3);
	Areas.Init(nullptr, 3);

	IsGameStarted = false;

	TArray<AActor*>Players;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABP_PlayerController::StaticClass(), Players);

	for (auto& Chel : Players)
	{
		Cast<ABP_PlayerController>(Chel)->RemoveFinalMenu();
		Cast<ABP_PlayerController>(Chel)->EnableOutline();
	}

	Cast<AGM>(UGameplayStatics::GetGameMode(GetWorld()))->Respawn();
}

void AGS::EventSpawnNote() {
	CodeGenerator = (1 + FMath::Rand() % 9) * 10000 + FMath::Rand() % 10 * 1000 + FMath::Rand() % 10 * 100 + FMath::Rand() % 10 * 10 + FMath::Rand() % 10;
	TArray<AActor*> GettingTagActors;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), ATargetPoint::StaticClass(), "NoteSpawn", GettingTagActors);
	GetWorld()->SpawnActor<ACodeNote_New>(CodeNoteClass, GettingTagActors[FMath::Rand() % GettingTagActors.Num()]->GetTransform());
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
				TArray<AActor*>Chelix;
				GeneratorAreaTmp->ShelterCollision->Collision->GetOverlappingActors(Chelix, AChel::StaticClass());
				for (auto& it : Chelix)
				{
					Cast<AChel>(it)->ShowUIAfterTerminalAndGenerator(-1, false);
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