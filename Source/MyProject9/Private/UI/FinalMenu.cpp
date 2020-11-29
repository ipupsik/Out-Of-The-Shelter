// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FinalMenu.h"
#include "BP_PlayerController.h"

void UFinalMenu::NativeConstruct() {
	Super::NativeConstruct();

	BTN_PlayMore->OnClicked.AddDynamic(this, &UFinalMenu::PlayMore);
}

void UFinalMenu::PlayMore()
{
	Player->ChangePlayersVoteCount();
}
