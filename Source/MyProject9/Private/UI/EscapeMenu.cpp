// Fill out your copyright notice in the Description page of Project Settings.


#include "UI\EscapeMenu.h"

void UEscapeMenu::NativeConstruct()
{
	UUserWidget::NativeConstruct();

	DoneButton->OnClicked.AddDynamic(this, &UEscapeMenu::OnClick);
}

void UEscapeMenu::OnClick()
{
	FPlatformMisc::ClipboardCopy(*NetID->GetText().ToString());
}

