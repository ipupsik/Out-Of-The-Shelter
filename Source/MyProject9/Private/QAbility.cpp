// Fill out your copyright notice in the Description page of Project Settings.


#include "QAbility.h"

FRotator UQAbility::GetCacheRotation(int32 CacheIndex)
{
	return FRotator();
}

FVector UQAbility::GetCacheLocation(int32 CacheIndex)
{
	return FVector();
}

bool UQAbility::UseAbilityClient(AChel* Player)
{
	return false;
}

void UQAbility::UseAbilityServer(AChel* Player)
{

}

bool UQAbility::DeUseAbilityClient(AChel* Player)
{
	return false;
}

void UQAbility::DeUseAbilityServer(AChel* Player)
{

}

FVector UQAbility::GetCacheScale3D(int32 CacheIndex)
{
	return FVector();
}