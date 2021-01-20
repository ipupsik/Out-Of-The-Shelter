// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VerstakWidget.generated.h"
/**
 * 
 */
class AChel;
class UVerstakWidget_Item;
UCLASS()
class MYPROJECT9_API UVerstakWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void NativeConstruct() override;
	UPROPERTY(EditAnywhere, Category = "Item")
		TSubclassOf<UVerstakWidget_Item> ItemClass;

	UFUNCTION(BlueprintImplementableEvent)
		void CallRefreshItemsBlueprint();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlOwner")
	AChel* WidgetOwner;
};
