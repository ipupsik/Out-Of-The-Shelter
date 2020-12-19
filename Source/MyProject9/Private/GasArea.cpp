// Fill out your copyright notice in the Description page of Project Settings.


#include "GasArea.h"
#include "Kismet/GameplayStatics.h"
#include "ParticleGasCPP.h"
#include "DamageAreaCPP.h"
#include "Engine/TargetPoint.h"
#include "Chel.h"

AGasArea::AGasArea() {
	areaType = CurrentAreaType;
}

void AGasArea::DoSomethink()
{
	bIsAvaliable = false;
	TArray<AActor*> PS_Targets;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), ATargetPoint::StaticClass(), GasAreaParticleTag, PS_Targets);

	for (auto& it : PS_Targets)
	{
		AParticleGasCPP* PSActor = GetWorld()->SpawnActor<AParticleGasCPP>(PS_Class, it->GetActorTransform());
		PSActor->areaType = areaType;
	}

	TArray<AActor*> DamageArea_Targets;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), ATargetPoint::StaticClass(), GasAreaDamageTag, DamageArea_Targets);

	for (auto& it : DamageArea_Targets)
	{
		ADamageAreaCPP* DamageActor = GetWorld()->SpawnActor<ADamageAreaCPP>(DamageAreaClass, it->GetActorTransform());
		if(DamageActor){
			DamageActor->areaType = areaType;
		}
		else {
		
		}
	}

	FTimerHandle FuzeTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(FuzeTimerHandle, this, &AGasArea::DeleteAllObjects, 20, false);
}

void AGasArea::DeleteAllObjects()
{
	bIsAvaliable = true;
	TArray<AActor*> PS_Targets;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AParticleGasCPP::StaticClass(), PS_Targets);

	for (auto& it : PS_Targets)
	{
		if (Cast<AParticleGasCPP>(it)->areaType == areaType)
		{
			it->Destroy();
		}
	}

	TArray<AActor*> DamageArea_Targets;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADamageAreaCPP::StaticClass(), DamageArea_Targets);

	for (auto& it : DamageArea_Targets)
	{
		if (Cast<ADamageAreaCPP>(it)->areaType == areaType)
		{
			it->Destroy();
		}
	}

	TArray<AActor*> Players;
	Collision->GetOverlappingActors(Players, AChel::StaticClass());

	for (auto& it : Players)
	{
//		Cast<AChel>(it)->ShowHudArea();
	}
}