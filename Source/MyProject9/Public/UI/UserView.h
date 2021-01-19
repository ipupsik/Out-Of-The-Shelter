// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Components/WidgetSwitcher.h"
#include "Components/VerticalBox.h"
#include "UI/RAbilitySlot.h"
#include "Components/HorizontalBox.h"
#include "Animation/WidgetAnimation.h"
#include "Components/HorizontalBoxSlot.h"
#include "UI/RadiationWidget.h"
#include "UI/QAbilitySlot.h"
#include "UI/RAbilitySlot.h"
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
	void AddDoubleRadiationEffect();
	void DisableDoubleRadiationEffect();
	void AddFreezeEffect();
	void DisableFreezeEffect();

	//void Construct() override;
public:
	AChel* Player;
	//---------------------------
	UPROPERTY(meta = (BindWidget))
		UTextBlock* AreaUsedText;

	UPROPERTY(meta = (BindWidget))
		UHorizontalBox* Effects_Bar;

	UPROPERTY(meta = (BindWidget))
		UImage* E_Mark;
	//---------------------------

	UPROPERTY(meta = (BindWidget))
		UTextBlock* AmmoLabel;

	TArray<UTextBlock*> ArrayCacheKey;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* KeyLeft_Bronze;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* KeyLeft_Silver;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* KeyLeft_Gold;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* AmmoMax;
	
	//---------------------------
	UPROPERTY(meta = (BindWidget)) //!!!!!!!!!!!!!!!!!!!!!!!
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
	UPROPERTY(meta = (BindWidget)) //!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		UProgressBar* PB_Opening;
	//---------------------------
	UPROPERTY(meta = (BindWidget))
		UImage* DarkScreen;
	//---------------------------
	UPROPERTY(meta = (BindWidget))
		UImage* Marker;
	//---------------------------

	TArray<UWidgetSwitcher*> ArraySwitcher;
	UPROPERTY(meta = (BindWidget))
		UWidgetSwitcher* WS_Boltorez;
	
	UPROPERTY(meta = (BindWidget))
		UWidgetSwitcher* WS_KeyShelter;

	UPROPERTY(meta = (BindWidget))
		UWidgetSwitcher* WS_Otvertka;
	//---------------------------

	UPROPERTY(meta = (BindWidgetAnim))
		UWidgetAnimation* Shading;

	UPROPERTY(meta = (BindWidgetAnim))
		UWidgetAnimation* CanalizaciaAnim;

	UPROPERTY(meta = (BindWidgetAnim))
		UWidgetAnimation* ShelterAnim;

	UPROPERTY(meta = (BindWidgetAnim))
		UWidgetAnimation* VentilaciaAnim;
	
	UPROPERTY(meta = (BindWidgetAnim))
		UWidgetAnimation* OpenAreaAnim;

	UPROPERTY(EditAnywhere, Category = "UI HUD")
		TSubclassOf<URadiationWidget> RadiationImage;
	
	UPROPERTY(EditAnywhere, Category = "UI HUD")
		TSubclassOf<UUserWidget> FreezeImage;

	UPROPERTY(meta = (BindWidget))
		URAbilitySlot* CurRSlot;

	UPROPERTY(meta = (BindWidget))
		UQAbilitySlot* CurQSlot;

	void NativeConstruct() override;

	bool IsAwake = true;
};
