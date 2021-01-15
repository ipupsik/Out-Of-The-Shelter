// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UI/FinalMenu.h"
#include "UI/Tab.h"

#include "BP_PlayerController.generated.h"

class AGS;

/**
 * 
 */
UCLASS()
class MYPROJECT9_API ABP_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void SetupInputComponent() override;

	ABP_PlayerController();
	void ShowTab();
	void UnShowTab();

	UFUNCTION(Client, Reliable)
		void AddFinalMenu();

	UFUNCTION(BlueprintImplementableEvent)
		void ToDoBlueprint();

	UFUNCTION(BlueprintImplementableEvent)
		void DisableOutline();

	UFUNCTION(BlueprintImplementableEvent)
		void EnableOutline();

	UFUNCTION(BlueprintImplementableEvent)
		void PlayGameplayMusic();

	void PlayMore();

	void BeginPlay() override;

	UFUNCTION(Server, Reliable, WithValidation)
		void ChangePlayersVoteCount();

	UFUNCTION(Client, Reliable, BlueprintCallable)
		void RefreshPlayersVoteCount(int32 Agreed, int32 Amount);

	UFUNCTION(Client, Reliable, BlueprintCallable)
		void RemoveFinalMenu();

public:
	bool AgreeSwitch;
	UPROPERTY(BlueprintReadOnly)
		bool IsHost;
	bool IsAccept;

	UPROPERTY(BlueprintReadOnly)
		AGS* GS;
	UFinalMenu* FinalMenu;
	UPROPERTY(BlueprintReadOnly)
		int32 Index;

	UTab* TabWidget;
};
