// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"


#include "NoteWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT9_API UNoteWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		UTextBlock* CodeText;

	void ChangeText(int32 Code);
	void NativeConstruct() override;
};
