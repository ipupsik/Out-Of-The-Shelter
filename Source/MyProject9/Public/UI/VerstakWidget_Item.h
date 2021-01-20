// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "GameFramework/Actor.h" 
#include "VerstakWidget_Item.generated.h"

/**
 * 
 */

UCLASS()
class MYPROJECT9_API UVerstakWidget_Item : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeConstruct() override;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UImage* Img;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* NameItem;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* Cost;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* CreateButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* CreatedItemClass;
	UFUNCTION(BlueprintCallable)
		void CreateEvent(AChel* Creator);
};
