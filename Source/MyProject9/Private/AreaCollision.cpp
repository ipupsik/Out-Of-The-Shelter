// Fill out your copyright notice in the Description page of Project Settings.


#include "AreaCollision.h"
#include "Chel.h"

// Sets default values
AAreaCollision::AAreaCollision()
{
	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	Collision->SetupAttachment(RootComponent);

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AAreaCollision::OnOverlapBegin);
	Collision->OnComponentEndOverlap.AddDynamic(this, &AAreaCollision::OnOverlapEnd);
}

void AAreaCollision::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	AChel* Player = Cast<AChel>(OtherActor);
	if (Player) {
		if (Player->IsPlayerOwner) {
			if (AreaType != 3) { //Не в двери выхода шелтора
				Player->UserView->PropmptTextArea->SetVisibility(ESlateVisibility::Visible);
				if (Player->IsPlayerOwner && !Player->GS->AreaClosed[AreaType]) {
					Player->CurCoreArea = this;
					if (AreaType == 1 && !Player->GS->IsShelterAvaliable) {
						Player->UserView->PropmptTextArea->SetText(AreaNotAvaliable);
						return;
					}
					if (AreaType == 2 && !Player->GS->IsVentilaciaAvaliable) {
						Player->UserView->PropmptTextArea->SetText(AreaNotAvaliable);
						return;
					}
					if (AreaType == 0 && !Player->GS->IsCanalizaciaAvaliable) {
						Player->UserView->PropmptTextArea->SetText(AreaNotAvaliable);
						return;
					}
					//*здесь была установка кода*
					if (!Player->GS->AreaAvaliables[AreaType])
					{
						if (Player->DoesHave[AreaType]) {
							Player->UserView->E_Mark->SetVisibility(ESlateVisibility::Visible);
							Player->UserView->PropmptTextArea->SetText(AreaAvaliableAndCanOpen);
						}
						else
							Player->UserView->PropmptTextArea->SetText(AreaAvaliableAndHaveNoItem);
						//Player->UserView->HoldText->SetVisibility(ESlateVisibility::Visible);
						
					}
					else
					{
						if (AreaType != 1) {
							Player->UserView->E_Mark->SetVisibility(ESlateVisibility::Visible);
							Player->UserView->PropmptTextArea->SetText(AreaOpenAndCanEscape);
						}
						//Player->UserView->EscapeText->SetVisibility(ESlateVisibility::Visible);
					}
				}
				else {
					Player->UserView->PropmptTextArea->SetText(AreaClose);
				}
			}
			else {
				if (Player->IsPlayerOwner) {
					if (!Player->GS->AreaClosed[1]) {
						Player->CurCoreArea = this;
						//Player->AreaCode = AreaType;
						if (Player->GS->AreaAvaliables[1]) {
							Player->UserView->E_Mark->SetVisibility(ESlateVisibility::Visible);
							Player->UserView->PropmptTextArea->SetText(AreaOpenAndCanEscape);
							Player->UserView->PropmptTextArea->SetVisibility(ESlateVisibility::Visible);
							//Player->UserView->EscapeText->SetVisibility(ESlateVisibility::Visible);

						}
						else {
							Player->UserView->PropmptTextArea->SetText(AreaNotAvaliable);
							Player->UserView->PropmptTextArea->SetVisibility(ESlateVisibility::Visible);
						}
					}
					else {
						Player->UserView->PropmptTextArea->SetText(AreaClose);
						Player->UserView->PropmptTextArea->SetVisibility(ESlateVisibility::Visible);
					}
				}
			}
		}
	}
}

void AAreaCollision::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AChel* Player = Cast<AChel>(OtherActor);
	if (Player) {
		if (Player->IsPlayerOwner) {
			if (AreaType != 3) { //Не в двери выхода шелтора
				if (Player->IsPlayerOwner && !Player->GS->AreaClosed[AreaType]) {
					//Player->AreaCode = -1;
					Player->CurCoreArea = nullptr;
					if (!Player->GS->AreaAvaliables[AreaType])
					{
						Player->IsSuccessOpening = false;
						Player->UserView->StopAllAnimations();
						//Player->UserView->PB_Opening->SetVisibility(ESlateVisibility::Hidden);
						
						//Player->UserView->HoldText->SetVisibility(ESlateVisibility::Hidden);
					}
					else
					{
						//if (AreaType != 1)
							//Player->UserView->PropmptTextArea->SetVisibility(ESlateVisibility::Hidden);
						//Player->UserView->EscapeText->SetVisibility(ESlateVisibility::Hidden);
					}
				}
				Player->UserView->PropmptTextArea->SetVisibility(ESlateVisibility::Hidden);
				if(!Player->LastInteractiveItem)
					Player->UserView->E_Mark->SetVisibility(ESlateVisibility::Hidden);
			}
			else {
				if (Player->IsPlayerOwner && !Player->GS->AreaClosed[1])
				{
					Player->CurCoreArea = nullptr;
					//Player->AreaCode = -1;
					//if (Player->GS->AreaAvaliables[1]) {
						//Player->UserView->PropmptTextArea->SetVisibility(ESlateVisibility::Hidden);
						//Player->UserView->EscapeText->SetVisibility(ESlateVisibility::Hidden);
					//}
				}
				if (!Player->LastInteractiveItem)
					Player->UserView->E_Mark->SetVisibility(ESlateVisibility::Hidden);
				Player->UserView->PropmptTextArea->SetVisibility(ESlateVisibility::Hidden);
			}
		}
	}
}

void AAreaCollision::PressedEAreaCollision(AChel* Player) {
	if (!Player->bInEscMenu && Player->bCanWalkingAndWatching) {
		if (AreaType >=0 && AreaType <= 2 && !Player->GS->AreaAvaliables[AreaType] && Player->DoesHave[AreaType]) {
			Player->UserView->PB_Opening->SetVisibility(ESlateVisibility::Visible);
			Player->UserView->TimeLeft->SetVisibility(ESlateVisibility::Visible);
		}
		switch (AreaType)
		{
			case 0: //канализация
			{
				if (Player->GS->AreaAvaliables[AreaType])
				{
					Player->PlayerEscape(AreaType);
					Player->UserView->RemoveFromParent();
				}
				else if (Player->DoesHave[AreaType])
				{
					Player->UserView->PlayAnimation(Player->UserView->CanalizaciaAnim);
				}
				break;
			}
			case 1: //замочная скважина шелтора
			{
				if (Player->DoesHave[AreaType] && !Player->GS->AreaAvaliables[AreaType])
				{
					Player->UserView->PlayAnimation(Player->UserView->ShelterAnim);
				}
				break;
			}
			case 2: //вентиляция
			{
				if (Player->GS->AreaAvaliables[AreaType])
				{
					Player->PlayerEscape(AreaType);
					Player->UserView->RemoveFromParent();
				}
				else if (Player->DoesHave[AreaType])
				{
					Player->UserView->PlayAnimation(Player->UserView->VentilaciaAnim);
				}
				break;
			}
			case 3: //выход шелтора(сама дверь)
			{
				if (Player->GS->AreaAvaliables[1]) {
					Player->PlayerEscape(1);
					Player->UserView->RemoveFromParent();
				}
			}
		}
	}
}


