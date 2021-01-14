// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/KDA_Stat.h"

void UKDA_Stat::NativeConstruct() {
	UUserWidget::NativeConstruct();
	KillsCount = 0;
	DeathsCount = 0;
}