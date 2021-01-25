// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"

#include "AreaCollision.generated.h"

class AChel;
UCLASS()
class MYPROJECT9_API AAreaCollision : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAreaCollision();

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// declare overlap end function
	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
		UBoxComponent* Collision;
	UPROPERTY(EditAnywhere)
	int32 AreaType;

	void PressedEAreaCollision(AChel* Player);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText AreaOpenAndCanEscape;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText AreaClose;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText AreaAvaliableAndHaveNoItem;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText AreaAvaliableAndCanOpen;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText AreaNotAvaliable;
};
