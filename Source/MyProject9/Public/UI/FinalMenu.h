// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

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
	UPROPERTY(meta = (BindWidget))
		UTextBlock* Ventilacia_Nickname;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* Canalizacia_Nickname;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* Shelter_Nickname;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* Ventilacia_Time;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* Canalizacia_Time;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* NickName;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* Shelter_Time;

	UPROPERTY(meta = (BindWidget))
		UButton* BTN_PlayMore;

	UPROPERTY(meta = (BindWidget))
		UButton* BTN_Exit;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* TB_PlayMore;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* TB_Exit;

public:
	UPROPERTY(BlueprintReadOnly)
		ABP_PlayerController* Player;
};
