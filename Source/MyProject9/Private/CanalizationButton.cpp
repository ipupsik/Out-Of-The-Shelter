// Fill out your copyright notice in the Description page of Project Settings.


#include "CanalizationButton.h"

// Sets default values
ACanalizationButton::ACanalizationButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	Collision->SetupAttachment(Mesh);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

	DoesRefresh = false;
}

// Called when the game starts or when spawned
void ACanalizationButton::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACanalizationButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACanalizationButton::Open()
{
	DoesRefresh = true;
	DisableCollision();
	ForwardAnimation();
	FTimerHandle FuzeTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(FuzeTimerHandle, this, &ACanalizationButton::Close, 5, false);
}

void ACanalizationButton::Close()
{
	if (DoesRefresh)
	{
		ReverceAnimation();
		FTimerHandle FuzeTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(FuzeTimerHandle, this, &ACanalizationButton::EnableCollision, 0.3, false);
	}
}

void ACanalizationButton::DisableCollision_Implementation()
{
	Collision->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
}

void ACanalizationButton::EnableCollision_Implementation()
{
	Collision->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
	DoesRefresh = false;
}

