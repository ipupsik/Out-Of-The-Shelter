// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UI/FinalMenu.h"

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
	ABP_PlayerController();

	UFUNCTION(Client, Reliable)
		void AddFinalMenu();

	void PlayMore();

	void BeginPlay() override;

	void Tick(float DeltaTime) override;

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
};
