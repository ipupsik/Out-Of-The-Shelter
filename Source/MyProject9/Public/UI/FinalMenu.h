// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/CircularThrobber.h"

#include "FinalMenu.generated.h"

/**
 * 
 */

class ABP_PlayerController;

UCLASS()
class MYPROJECT9_API UFinalMenu : public UUserWidget
{
	GENERATED_BODY()
public:
    void NativeConstruct() override;
	UFUNCTION()
		void PlayMore();
public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* BTN_PlayMore;

	UPROPERTY(EditAnywhere)
		FSlateColor ColorAgreePlayer;
	UPROPERTY(EditAnywhere)
		FSlateColor ColorNotAgreePlayer;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* BTN_Exit;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* TB_PlayMore;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* TB_Exit;

	bool IsClicked;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* TB_Restart;

	UPROPERTY(meta = (BindWidget))
		UCircularThrobber* Throbbler;

public:
	UPROPERTY(BlueprintReadOnly)
		ABP_PlayerController* Player;
};
