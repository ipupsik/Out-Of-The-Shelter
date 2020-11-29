// Fill out your copyright notice in the Description page of Project Settings.


#include "WebCamSpectator.h"

// Sets default values
AWebCamSpectator::AWebCamSpectator()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(RootComponent);

	Index = -1;
}

// Called when the game starts or when spawned
void AWebCamSpectator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWebCamSpectator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AWebCamSpectator::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//PlayerInputComponent->BindAxis("LookUp", this, &AWebCamSpectator::LookUp);
	//PlayerInputComponent->BindAxis("LookRight", this, &AWebCamSpectator::LookRight);

	//PlayerInputComponent->BindAction("UpdateSpectating_Left", IE_Pressed, this, &AWebCamSpectator::ChangeSpecLeft);
	//PlayerInputComponent->BindAction("UpdateSpectating_Right", IE_Pressed, this, &AWebCamSpectator::ChangeSpecRight);
}

