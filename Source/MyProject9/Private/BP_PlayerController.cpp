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
	IsShiftPressed = false;
	WidgetStack = 0;
}

void ABP_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	GS = GetWorld()->GetGameState<AGS>();
	//TabWidget->AddToViewport(1);
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
	WidgetStack++;
	TabWidget->SetVisibility(ESlateVisibility::Visible);

	AChel* CurPawn = Cast<AChel>(GetPawn());
	if (CurPawn) {
		FInputModeGameAndUI InputUI;
		SetInputMode(InputUI);
		if (CurPawn) {
			CurPawn->ShowInventory();
		}
	}
}

void ABP_PlayerController::UnShowTab()
{
	bInTabMenu = false;
	if(WidgetStack != 0)
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
			TArray<AActor*>PlayerControllers;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABP_PlayerController::StaticClass(), PlayerControllers);
			for (auto PC : PlayerControllers) {
				Cast<ABP_PlayerController>(PC)->RemoveFinalMenu();
			}
			GS->ResetGame();
		}
		else {
			TArray<AActor*>PlayerControllers;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABP_PlayerController::StaticClass(), PlayerControllers);
			for (auto PC : PlayerControllers) {
				Cast<ABP_PlayerController>(PC)->RefreshPlayersVoteCount(GS->AgreedPlayers + 1, GS->AmountOfPlayers);
			}
			GS->AgreedPlayers++;
		}
		FinalMenu->TB_Restart->SetColorAndOpacity(FinalMenu->ColorAgreePlayer);
	}
	else
	{
		TArray<AActor*>PlayerControllers;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABP_PlayerController::StaticClass(), PlayerControllers);
		for (auto PC : PlayerControllers) {
			Cast<ABP_PlayerController>(PC)->RefreshPlayersVoteCount(GS->AgreedPlayers - 1, GS->AmountOfPlayers);
		}
		GS->AgreedPlayers--;
		FinalMenu->TB_Restart->SetColorAndOpacity(FinalMenu->ColorNotAgreePlayer);
	}
	IsAccept = !IsAccept;
}

bool ABP_PlayerController::ChangePlayersVoteCount_Validate()
{
	return true;
}

void ABP_PlayerController::RemoveFinalMenu_Implementation()
{
	bShowMouseCursor = false;
	if (FinalMenu) {
		FinalMenu->TB_Restart->SetVisibility(ESlateVisibility::Visible);
		FinalMenu->Throbbler->SetVisibility(ESlateVisibility::Visible);
		FinalMenu->BTN_PlayMore->SetVisibility(ESlateVisibility::Hidden);
		FinalMenu->BTN_Exit->SetVisibility(ESlateVisibility::Hidden);
	}
}