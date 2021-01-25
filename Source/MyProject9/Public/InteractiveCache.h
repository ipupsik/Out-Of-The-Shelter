// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveItem.h"
#include "InteractiveCache.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT9_API AInteractiveCache : public AInteractiveItem
{
	GENERATED_BODY()
public:
	virtual void PickUpEventServer(AChel* Player) override;
	virtual bool PickUpEventClient(AChel* Player) override;
	virtual void OnLineTraced(AChel* Player) override;
public:
	AInteractiveCache();

	virtual void ToggleCustomDepth(bool NewIsOutliningNow, AChel* Player) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void Open();

	UFUNCTION(NetMulticast, Reliable)
		void DisableEverywhere();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 CacheType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 CacheIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Collision")
		UBoxComponent* Collision;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Scene")
		USceneComponent* Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Scene")
		USceneComponent* MainScene;
};
