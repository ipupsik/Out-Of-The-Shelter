// Fill out your copyright notice in the Description page of Project Settings.


#include "Cache.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ACache::ACache()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MainScene = CreateDefaultSubobject<USceneComponent>("MainScene");
	MainScene->SetupAttachment(RootComponent);

	Scene = CreateDefaultSubobject<USceneComponent>("Scene");
	Scene->SetupAttachment(MainScene);

	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	Collision->SetupAttachment(Scene);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(Scene);

	IsEnabled = true;
}

void ACache::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACache, IsEnabled);
}

// Called when the game starts or when spawned
void ACache::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACache::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


