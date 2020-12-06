// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GeneratorWidget.h"

void UGeneratorWidget::NativeConstruct() {
	Super::NativeConstruct();

	ChangeCorretcaPosition(0);
	
	TickEnable = true;
}

void UGeneratorWidget::ChangeCorretcaPosition(int32 TypeChange) {
	Corretca->SetValue(PositionX[TypeChange]);
	PB_Repair->SetPercent(0.0f);
	bToRight = true;
	curSpeed = Speed[TypeChange];
}

void UGeneratorWidget::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	if (TickEnable) {
		Super::NativeTick(MyGeometry, DeltaTime);
		if (bToRight) {
			PB_Repair->SetPercent(PB_Repair->Percent + (curSpeed + FMath::FRand() * delta) * DeltaTime);
			if (PB_Repair->Percent >= 1.0f) {
				bToRight = false;
			}
		}
		else {
			PB_Repair->SetPercent(PB_Repair->Percent - (curSpeed + FMath::FRand() * delta) * DeltaTime);
			if (PB_Repair->Percent <= 0.0f) {
				bToRight = true;
			}
		}
	}

}
