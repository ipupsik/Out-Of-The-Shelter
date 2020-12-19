// Fill out your copyright notice in the Description page of Project Settings.


#include "GasAreaVentil.h"
#include "Kismet/GameplayStatics.h"
#include "ParticleGasCPP.h"
#include "DamageAreaCPP.h"
#include "Engine/TargetPoint.h"
#include "Chel.h"

AGasAreaVentil::AGasAreaVentil() {
	areaType = CurrentAreaType;
}

void AGasAreaVentil::DoSomethink()
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
		if (DamageActor) {
			DamageActor->areaType = areaType;
		}
		else {

		}
	}

	FTimerHandle FuzeTimerHandle1;
	GetWorld()->GetTimerManager().SetTimer(FuzeTimerHandle1, this, &AOpenArea::RotateVentilServerReverse, 10, false);

	FTimerHandle FuzeTimerHandle2;
	GetWorld()->GetTimerManager().SetTimer(FuzeTimerHandle2, this, &AGasAreaVentil::DeleteAllObjects, 21, false);
}

void AGasAreaVentil::DeleteAllObjects()
{
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

	bIsAvaliable = true;
}