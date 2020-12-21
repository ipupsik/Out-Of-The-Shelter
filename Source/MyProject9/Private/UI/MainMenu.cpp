// Fill out your copyright notice in the Description page of Project Settings.


#include "UI\MainMenu.h"

void UMainMenu::NativeConstruct()
{
	UUserWidget::NativeConstruct();

	PasteButton->OnClicked.AddDynamic(this, &UMainMenu::OnClick);
}

void UMainMenu::OnClick()
{
	FString Temp;
	FPlatformMisc::ClipboardPaste(Temp);
	ServerConnectID->SetText(FText::FromString(Temp));
}
