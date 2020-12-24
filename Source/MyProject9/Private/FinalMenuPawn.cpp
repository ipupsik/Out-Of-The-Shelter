// Fill out your copyright notice in the Description page of Project Settings.


#include "FinalMenuPawn.h"

// Sets default values
AFinalMenuPawn::AFinalMenuPawn()
{
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
}