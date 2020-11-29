// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Components/WidgetSwitcher.h"
#include "Components/VerticalBox.h"
#include "Animation/WidgetAnimation.h"

#include "UserView.generated.h"


class AChel;
/**
 * 
 */

UCLASS()
class MYPROJECT9_API UUserView : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;

	//void Construct() override;
public:
	AChel* Player;
	//---------------------------
	UPROPERTY(meta = (BindWidget))
		UTextBlock* PickUpLabel_Otvertka;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* PickUpLabel_KeyShelter;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* PickUpLabel_Boltorez;
	//---------------------------

	UPROPERTY(meta = (BindWidget))
		UTextBlock* AmmoLabel;
	//---------------------------
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) //!!!!!!!!!!!!!!!!!!!!!!!
		UTextBlock* TimeLeft;

	//---------------------------
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))  //!!!!!!!!!!!!!!!!!!!!!!!
		UTextBlock* HoldText;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* EscapeText;
	//---------------------------
	UPROPERTY(meta = (BindWidget))
		UProgressBar* RadiationPoints;
	//---------------------------
	UPROPERTY(BlueprintReadWrite,  meta = (BindWidget)) //!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		UProgressBar* PB_Opening;
	//---------------------------
	UPROPERTY(meta = (BindWidget))
		UImage* DarkScreen;
	//---------------------------
	UPROPERTY(meta = (BindWidget))
		UImage* Marker;
	//---------------------------
	UPROPERTY(meta = (BindWidget))
		UWidgetSwitcher* WS_Boltorez;
	
	UPROPERTY(meta = (BindWidget))
		UWidgetSwitcher* WS_KeyShelter;

	UPROPERTY(meta = (BindWidget))
		UWidgetSwitcher* WS_Otvertka;
	//---------------------------
	UPROPERTY(meta = (BindWidget))
		UVerticalBox* VB_KillFeed;
	//---------------------------

	UPROPERTY(meta = (BindWidgetAnim))
		UWidgetAnimation* Shading;

	UPROPERTY(meta = (BindWidgetAnim))
		UWidgetAnimation* CanalizaciaAnim;

	UPROPERTY(meta = (BindWidgetAnim))
		UWidgetAnimation* ShelterAnim;

	UPROPERTY(meta = (BindWidgetAnim))
		UWidgetAnimation* VentilaciaAnim;

	void NativeConstruct() override;

	bool IsAwake;
};
