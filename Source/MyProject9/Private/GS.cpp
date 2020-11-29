// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "GS.h" 
#include "Kismet/GameplayStatics.h"
#include "Chel.h"
#include "Engine/TargetPoint.h"
#include "AreaCollision.h"
#include "GM.h"

AGS::AGS() {
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
}

void AGS::GameBegin() {

	TArray<AActor*>FindAreas;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAreaCollision::StaticClass(), FindAreas);
	for (auto FindArea : FindAreas) {
		Areas[Cast<AAreaCollision>(FindArea)->AreaType] = Cast<AAreaCollision>(FindArea);
	}
	UE_LOG(LogTemp, Warning, TEXT("%d"), Areas.Num());

	IsGameStarted = true;
	TArray<AActor*> Players;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AChel::StaticClass(), Players);
	for (auto Player : Players) {
		UE_LOG(LogTemp, Warning, TEXT("SpawnAnimationGS"));
		AChel* Chel = Cast<AChel>(Player);
		Chel->PlaySpawnAnimationSleep();
	}

	TArray<AActor*>TargetPoints_KeyShelter;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), ATargetPoint::StaticClass(), FName("KeyShelter"), TargetPoints_KeyShelter);

	CurrentKeyShelter = MIN_COUNT_KeyShelter + FMath::Rand() % (MAX_COUNT_Boltorez - MIN_COUNT_KeyShelter + 1);
	for (int i = 0; i < CurrentKeyShelter; ++i) {
		GetWorld()->SpawnActor<AActor>(KeyShelter, TargetPoints_KeyShelter[i]->GetActorTransform());
	}

	TArray<AActor*>TargetPoints_Boltorez;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), ATargetPoint::StaticClass(), FName("Boltorez"), TargetPoints_Boltorez);

	CurrentBoltorez = MIN_COUNT_Boltorez + FMath::Rand() % (MAX_COUNT_Boltorez - MIN_COUNT_Boltorez + 1);
	for (int i = 0; i < MIN_COUNT_Boltorez + FMath::Rand() % (MAX_COUNT_Boltorez - MIN_COUNT_Boltorez + 1); ++i) {
		GetWorld()->SpawnActor<AActor>(Boltorez, TargetPoints_Boltorez[i]->GetActorTransform());
	}

	TArray<AActor*>TargetPoints_Otvertka;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), ATargetPoint::StaticClass(), FName("Otvertka"), TargetPoints_Otvertka);

	CurrentOtvertka = MIN_COUNT_Otvertka + FMath::Rand() % (MAX_COUNT_Otvertka - MIN_COUNT_Otvertka + 1);
	for (int i = 0; i < CurrentOtvertka; ++i) {
		GetWorld()->SpawnActor<AActor>(Otvertka, TargetPoints_Otvertka[i]->GetActorTransform());
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