// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_PlayerController.h"
#include "GI.h"
#include "GS.h"
#include "Kismet/GameplayStatics.h"

ABP_PlayerController::ABP_PlayerController()
{
	bReplicates = true;
	IsAccept = true;
	IsHost = false;
}

void ABP_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	GS = GetWorld()->GetGameState<AGS>();
}

void ABP_PlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABP_PlayerController::RefreshPlayersVoteCount_Implementation(int32 Agreed, int32 Amount)
{
	FText NewText = FText::Format(FText::FromString(TEXT("Play More {0}/{1}")), Agreed, Amount);
	FinalMenu->TB_PlayMore->SetText(NewText);
}

void ABP_PlayerController::AddFinalMenu_Implementation()
{
	FinalMenu = Cast<UFinalMenu>(CreateWidget(this, Cast<UGI>(GetGameInstance())->FinalMenuClass));
	FinalMenu->Player = this;
	FinalMenu->AddToViewport();

	bShowMouseCursor = true;
	DisableInput(this);
	
}

void ABP_PlayerController::ChangePlayersVoteCount_Implementation()
{
	if (IsAccept)
	{
		if ((GS->AgreedPlayers + 1) == GS->AmountOfPlayers)
		{
			GS->ResetGame();
			RemoveFinalMenu();
		}
		else {
			TArray<AActor*>PlayerControllers;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABP_PlayerController::StaticClass(), PlayerControllers);
			for (auto PC : PlayerControllers) {
				Cast<ABP_PlayerController>(PC)->RefreshPlayersVoteCount(GS->AgreedPlayers + 1, GS->AmountOfPlayers);
			}
			GS->AgreedPlayers++;
		}
	}
	else
	{
		TArray<AActor*>PlayerControllers;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABP_PlayerController::StaticClass(), PlayerControllers);
		for (auto PC : PlayerControllers) {
			Cast<ABP_PlayerController>(PC)->RefreshPlayersVoteCount(GS->AgreedPlayers - 1, GS->AmountOfPlayers);
		}
		GS->AgreedPlayers--;
	}
	IsAccept = !IsAccept;
}

bool ABP_PlayerController::ChangePlayersVoteCount_Validate()
{
	return true;
}

void ABP_PlayerController::RemoveFinalMenu_Implementation()
{
	FinalMenu->RemoveFromParent();
	bShowMouseCursor = false;
}