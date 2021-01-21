// Fill out your copyright notice in the Description page of Project Settings.


#include "QAbility_Rentgen.h"
#include "GS.h"
#include "InteractiveCache.h"

FVector UQAbility_Rentgen::GetCacheScale3D(int32 CacheIndex)
{
	AGS* MyGS = GetWorld()->GetGameState<AGS>();
	return MyGS->RentgenGlassTransform[MyGS->Caches[CacheIndex]->CacheIndex].GetScale3D();
}

FRotator UQAbility_Rentgen::GetCacheRotation(int32 CacheIndex)
{
	AGS* MyGS = GetWorld()->GetGameState<AGS>();
	return FRotator(MyGS->RentgenGlassTransform[MyGS->Caches[CacheIndex]->CacheIndex].GetRotation());
}

FVector UQAbility_Rentgen::GetCacheLocation(int32 CacheIndex)
{
	AGS* MyGS = GetWorld()->GetGameState<AGS>();
	return MyGS->RentgenGlassTransform[MyGS->Caches[CacheIndex]->CacheIndex].GetLocation();
}
