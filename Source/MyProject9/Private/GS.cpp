// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "GS.h" 
#include "Kismet/GameplayStatics.h"
#include "Chel.h"
#include "Engine/TargetPoint.h"
#include "AreaCollision.h"
#include "GM.h"
#include "Cache_Key.h"
#include "WebCamPoint.h"

AGS::AGS() {
	NickNames.Init(FText::FromString(TEXT(" ")), 4);
	Kills.Init(FText::FromString(TEXT("0")), 4);
	Deaths.Init(FText::FromString(TEXT("1")), 4);
	Winners.Init(FText::FromString(TEXT("")), 3);
	WebCam_Rotation.Init({}, 0);
	WebCam_Location.Init({}, 0);
	WebCam_IsEnabled.Init(true, 0);
	Keys_Transform.Init({}, 0);
	Keys_IsAvaliable.Init(true, 0);
	CacheItems_Stuff_Transform.Init({}, 0);
	CacheItems_Stuff_IsAvaliable.Init(true, 0);
	EscapeTime.Init(0, 4);
	AcceptPiedistalAmount = 0;
	AmountOfPlayers = 0;
	AgreedPlayers = 0;

	GeneralLayer = 0;
	AreaAvaliables.Init(false, 3);
	AreaClosed.Init(false, 3);
	Areas.Init(nullptr, 3);

	IsGameStarted = false;

	CurrentButtonCount = 0;

	CodeGenerator = -1;
	CurrentCode = 0;
	IsCodeTerminalAvaliable = false;
	ButtonPlayAnim = false;
	NumbersOnPanel.Init(nullptr, 0);
}

void AGS::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGS, NickNames);
	DOREPLIFETIME(AGS, Kills);
	DOREPLIFETIME(AGS, Deaths);
	DOREPLIFETIME(AGS, EscapeTime);
	DOREPLIFETIME(AGS, AreaAvaliables);
	DOREPLIFETIME(AGS, AreaClosed);
	DOREPLIFETIME(AGS, WebCam_Rotation);
	DOREPLIFETIME(AGS, WebCam_Location);
	DOREPLIFETIME(AGS, WebCam_IsEnabled);
	DOREPLIFETIME(AGS, CodeGenerator);
	DOREPLIFETIME(AGS, IsCodeTerminalAvaliable);
	DOREPLIFETIME(AGS, ButtonPlayAnim);
	DOREPLIFETIME(AGS, NumbersOnPanel);
}

void AGS::BeginPlay()
{
	Super::BeginPlay();

	if (GetLocalRole() == ROLE_Authority) {
		TArray<AActor*>FindAreas;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAreaCollision::StaticClass(), FindAreas);
		for (auto FindArea : FindAreas) {
			Areas[Cast<AAreaCollision>(FindArea)->AreaType] = Cast<AAreaCollision>(FindArea);
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
			WebCam_Location.Add(WebCamSpectators[i]->GetActorLocation());
			WebCam_Rotation.Add(WebCamSpectators[i]->GetActorRotation());
			WebCam_IsEnabled.Add(true);
		}

		//----------------------------Cache Items

		TArray<AActor*>TargetPoints_CacheItems;
		UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), ATargetPoint::StaticClass(), FName("CacheItems"), TargetPoints_CacheItems);
		
		for (int i = 0; i < TargetPoints_CacheItems.Num(); ++i)
		{
			CacheItems_Stuff_Transform.Add(TargetPoints_CacheItems[i]->GetActorTransform());
			CacheItems_Stuff_IsAvaliable.Add(true);
		}

		for (int i = 0; i < 4; i++)
		{
			int ArrayIndex = 0;
			while (!CacheItems_Stuff_IsAvaliable[ArrayIndex])
			{
				ArrayIndex = FMath::Rand() % CacheItems_Stuff_IsAvaliable.Num();
			}

			AActor* NewItem = GetWorld()->SpawnActor<AActor>(InvisiblePotion, CacheItems_Stuff_Transform[ArrayIndex]);

			if (NewItem)
				CacheItems_Stuff_IsAvaliable[ArrayIndex] = false;
		}

		CurrentKeyShelter = MIN_COUNT_KeyShelter + FMath::Rand() % (MAX_COUNT_Boltorez - MIN_COUNT_KeyShelter + 1);
		for (int i = 0; i < CurrentKeyShelter; ++i) {
			int ArrayIndex = 0;
			while (!CacheItems_Stuff_IsAvaliable[ArrayIndex])
			{
				ArrayIndex = FMath::Rand() % CacheItems_Stuff_IsAvaliable.Num();
			}

			AActor* NewItem = GetWorld()->SpawnActor<AActor>(KeyShelter, CacheItems_Stuff_Transform[ArrayIndex]);

			if (NewItem)
				CacheItems_Stuff_IsAvaliable[ArrayIndex] = false;
		}

		CurrentBoltorez = MIN_COUNT_Boltorez + FMath::Rand() % (MAX_COUNT_Boltorez - MIN_COUNT_Boltorez + 1);
		for (int i = 0; i < MIN_COUNT_Boltorez + FMath::Rand() % (MAX_COUNT_Boltorez - MIN_COUNT_Boltorez + 1); ++i) {
			int ArrayIndex = 0;
			while (!CacheItems_Stuff_IsAvaliable[ArrayIndex])
			{
				ArrayIndex = FMath::Rand() % CacheItems_Stuff_IsAvaliable.Num();
			}

			AActor* NewItem = GetWorld()->SpawnActor<AActor>(Boltorez, CacheItems_Stuff_Transform[ArrayIndex]);

			if (NewItem)
				CacheItems_Stuff_IsAvaliable[ArrayIndex] = false;
		}

		CurrentOtvertka = MIN_COUNT_Otvertka + FMath::Rand() % (MAX_COUNT_Otvertka - MIN_COUNT_Otvertka + 1);
		for (int i = 0; i < CurrentOtvertka; ++i) {
			int ArrayIndex = 0;
			while (!CacheItems_Stuff_IsAvaliable[ArrayIndex])
			{
				ArrayIndex = FMath::Rand() % CacheItems_Stuff_IsAvaliable.Num();
			}

			AActor* NewItem = GetWorld()->SpawnActor<AActor>(Otvertka, CacheItems_Stuff_Transform[ArrayIndex]);

			if (NewItem)
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
			for (int i = 0; i < COUNT_CacheKey; i++)
			{
				int ArrayIndex = 0;
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
					Cast<ACache_Key>(NewItem)->ArrayIndex = ArrayIndex;
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
	for (auto Player : Players) {
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
		Player->Ammo = 10;
		Player->IsInGame = true;
		Player->Health = 0;
		Player->Stone->SetHiddenInGame(false);
	}
}

void AGS::ResetGame() {
	TArray<AActor*>Stuff;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APickableItem::StaticClass(), Stuff);

	for (auto Obj : Stuff)
		Obj->Destroy();

	NickNames.Init(FText::FromString(TEXT(" ")), 4);
	Kills.Init(FText::FromString(TEXT("0")), 4);
	Deaths.Init(FText::FromString(TEXT("1")), 4);
	Winners.Init(FText::FromString(TEXT("")), 3);
	EscapeTime.Init(0, 4);
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

	for (auto Chel : Players)
		Cast<ABP_PlayerController>(Chel)->RemoveFinalMenu();

	Cast<AGM>(UGameplayStatics::GetGameMode(GetWorld()))->Respawn();
}

void AGS::EventSpawnNote() {
	CodeGenerator = (1 + FMath::Rand() % 9) * 10000 + FMath::Rand() % 10 * 1000 + FMath::Rand() % 10 * 100 + FMath::Rand() % 10 * 10 + FMath::Rand() % 10;
	TArray<AActor*> GettingTagActors;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), ATargetPoint::StaticClass(), "NoteSpawn", GettingTagActors);
	GetWorld()->SpawnActor<ACode_Note>(CodeNoteClass, GettingTagActors[FMath::Rand() % GettingTagActors.Num()]->GetTransform());
	IsCodeTerminalAvaliable = true;
}

void AGS::AddNumToTerminal(int32 Number) {
	FTransform Trans;
	Trans.SetLocation(FVector(TransformOfFirstNum.GetLocation().X + 7 * NumbersOnPanel.Num(), TransformOfFirstNum.GetLocation().Y, TransformOfFirstNum.GetLocation().Z));
	Trans.SetRotation(TransformOfFirstNum.GetRotation());
	Trans.SetScale3D(TransformOfFirstNum.GetScale3D());
	ANumberTerminal* Num = GetWorld()->SpawnActorDeferred<ANumberTerminal>(NumberTerminalClass, Trans);
	if (Num != nullptr) 
	{
		Num->NumberType = Number;
		UGameplayStatics::FinishSpawningActor(Num, Trans);
		if (Num != nullptr)
			NumbersOnPanel.Add(Num);
	}
}

void AGS::DeleteLastNumber() {
	NumbersOnPanel[NumbersOnPanel.Num() - 1]->Destroy();
	NumbersOnPanel.Pop();
}

void AGS::CheckCode(int Index) {
	CurrentCode = 0;
	if (NumbersOnPanel.Num() == 5) {
		CurrentCode = NumbersOnPanel[0]->NumberType * 10000 + NumbersOnPanel[1]->NumberType * 1000 + NumbersOnPanel[2]->NumberType * 100 + NumbersOnPanel[3]->NumberType * 10 + NumbersOnPanel[4]->NumberType;
		if (CurrentCode == CodeGenerator) {
			TArray<AActor*> GettingChelix;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), AChel::StaticClass(), GettingChelix);
			for (auto& it : GettingChelix) 
			{
				Cast<AChel>(it)->HideNoteWidget();
			}
			

			TArray<AActor*> GettingCodeNote;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACode_Note::StaticClass(), GettingCodeNote);
			for (auto& it : GettingCodeNote)
			{
				Cast<ACode_Note>(it)->Destroy();
			}

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

			IsCodeTerminalAvaliable = false;

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
	TArray<AActor*> Generator;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGeneratorArea::StaticClass(), Generator);

	if (Generator[0])
		Cast<AGeneratorArea>(Generator[0])->RefreshGenerator();
}