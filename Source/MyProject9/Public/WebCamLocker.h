// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"

#include "WebCamLocker.generated.h"

UCLASS()
class MYPROJECT9_API AWebCamLocker : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWebCamLocker();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable) //легендарна€ св€зќчка
		void Open();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable) //легендарна€ св€зќчка
		void Close();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
		UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
		UBoxComponent* Collision;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
		USceneComponent* Scene;
public:
	bool DoesLock;
	UPROPERTY(EditAnywhere)
	int32 Index;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool DoesPlayAnim;
};
