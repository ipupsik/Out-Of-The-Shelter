// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"

#include "Cache.generated.h"

UCLASS()
class MYPROJECT9_API ACache : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACache();

protected:
public:
	// Called when the game starts or when spawned
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void Opening();
public:	
	void GetLifetimeReplicatedProps(TArray < FLifetimeProperty >& OutLifetimeProps) const override;
	// Called every frame

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 CacheType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 CacheIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
		UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
		UBoxComponent* Collision;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
		USceneComponent* MainScene;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
		USceneComponent* Scene;

	UPROPERTY(BlueprintReadWrite, Replicated)
		bool IsEnabled;
};
