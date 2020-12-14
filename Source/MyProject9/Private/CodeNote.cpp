// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeNote.h"

// Sets default values
ACodeNote::ACodeNote()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACodeNote::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACodeNote::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

