// Fill out your copyright notice in the Description page of Project Settings.


#include "UI\NoteWidget.h"

void UNoteWidget::NativeConstruct() {
	UUserWidget::NativeConstruct();
}

void UNoteWidget::ChangeText(int32 Code){
	CodeText->SetText(FText::AsNumber(Code));
}
