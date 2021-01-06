// Fill out your copyright notice in the Description page of Project Settings.


#include "Stone.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Chel.h"

// Sets default values
AStone::AStone()
{
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));

	Stone = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Stone"));
	Stone->SetupAttachment(RootComponent);
}