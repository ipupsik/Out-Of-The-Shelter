// Fill out your copyright notice in the Description page of Project Settings.


#include "WebCamLocker.h"

// Sets default values
AWebCamLocker::AWebCamLocker()
{
	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	Collision->SetupAttachment(RootComponent);
	Scene = CreateDefaultSubobject<USceneComponent>("Scene");
	Scene->SetupAttachment(Collision);
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(Scene);

	DoesLock = false;
	Index = 0;
	DoesPlayAnim = false;
}

