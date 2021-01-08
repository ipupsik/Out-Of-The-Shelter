// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonCanalization.h"

// Sets default values
AButtonCanalization::AButtonCanalization()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	Collision->SetupAttachment(Mesh);

	DoesRefresh = false;
}

void AButtonCanalization::Open()
{
	DoesRefresh = true;
	DisableCollision();
	ForwardAnimation();
	FTimerHandle FuzeTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(FuzeTimerHandle, this, &AButtonCanalization::Close, 10, false);
}

void AButtonCanalization::Close()
{
	if (DoesRefresh)
	{
		ReverceAnimation();
		FTimerHandle FuzeTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(FuzeTimerHandle, this, &AButtonCanalization::EnableCollision, 0.3, false);
	}
}

void AButtonCanalization::DisableCollision_Implementation()
{
	Collision->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
}

void AButtonCanalization::EnableCollision_Implementation()
{
	Collision->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
	DoesRefresh = false;
}
