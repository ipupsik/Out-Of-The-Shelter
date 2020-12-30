// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemPromtArrow.h"

// Sets default values
AItemPromtArrow::AItemPromtArrow()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->bRenderInDepthPass = true;
	Mesh->CustomDepthStencilValue = 0;
}
