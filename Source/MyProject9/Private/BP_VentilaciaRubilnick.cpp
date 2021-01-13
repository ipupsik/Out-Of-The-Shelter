// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_VentilaciaRubilnick.h"
#include "GS.h"
#include "Kismet/GameplayStatics.h"
#include "VentilaciaGenerator.h"

ABP_VentilaciaRubilnick::ABP_VentilaciaRubilnick()
{
	is_Avaliable = true;
}

void ABP_VentilaciaRubilnick::CheckVentilaciaAvaliable()
{
	AGS* MyGS = GetWorld()->GetGameState<AGS>();
	MyGS->VentilaciaRubilnickCount--;
	Open();
	ChangeAvaliable();
	if (MyGS->VentilaciaRubilnickCount == 0)
	{
		MyGS->IsVentilaciaAvaliable = true;
		TArray<AActor*>VentilaciaGenerator;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AVentilaciaGenerator::StaticClass(), VentilaciaGenerator);
		if (VentilaciaGenerator.Num() > 0)
			Cast<AVentilaciaGenerator>(VentilaciaGenerator[0])->Close();
	}
}

void ABP_VentilaciaRubilnick::ChangeAvaliable_Implementation()
{
	is_Avaliable = false;
}