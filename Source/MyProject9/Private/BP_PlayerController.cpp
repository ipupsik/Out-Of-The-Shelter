// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_PlayerController.h"
#include "GI.h"
#include "GS.h"
#include "Chel.h"
#include "Kismet/GameplayStatics.h"

ABP_PlayerController::ABP_PlayerController()
{
	bReplicates = true;
	IsAccept = true;
	IsHost = false;
	bInTabMenu = false;
}

void ABP_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	GS = GetWorld()->GetGameState<AGS>();
}

void ABP_PlayerController::RefreshPlayersVoteCount_Implementation(int32 Agreed, int32 Amount)
{
	FText NewText = FText::Format(FText::FromString(TEXT("Play More {0}/{1}")), Agreed, Amount);
	FinalMenu->TB_PlayMore->SetText(NewText);
}

void ABP_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("TabStat", IE_Pressed, this, &ABP_PlayerController::ShowTab);
	InputComponent->BindAction("TabStat", IE_Released, this, &ABP_PlayerController::UnShowTab);
}

//KillFeed --------------------
void ABP_PlayerController::ShowTab()
{
	bInTabMenu = true;
	bShowMouseCursor = true;
	TabWidget->SetVisibility(ESlateVisibility::Visible);
	FInputModeGameAndUI InputUI;
	InputUI.SetWidgetToFocus(Cast<AChel>(GetPawn())->MyInventory->TakeWidget());
	InputUI.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	SetInputMode(InputUI);
	if (Cast<AChel>(GetPawn())) {
		Cast<AChel>(GetPawn())->ShowInventory();
	}
}

void ABP_PlayerController::UnShowTab()
{
	bInTabMenu = false;
	WidgetStack--;
	AChel* Plr = Cast<AChel>(GetPawn());
	if (WidgetStack == 0)
	{
		bShowMouseCursor = false;
		FInputModeGameOnly GameUI;
		SetInputMode(GameUI);
	}
	TabWidget->SetVisibility(ESlateVisibility::Hidden);
	if (Cast<AChel>(GetPawn())) {
		Cast<AChel>(GetPawn())->UnShowInventory();
	}
}

void ABP_PlayerController::AddFinalMenu_Implementation()
{
	FinalMenu = Cast<UFinalMenu>(CreateWidget(this, Cast<UGI>(GetGameInstance())->FinalMenuClass));
	DisableOutline();
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