// Fill out your copyright notice in the Description page of Project Settings.


#include "WebCamLocker.h"

// Sets default values
AWebCamLocker::AWebCamLocker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


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

