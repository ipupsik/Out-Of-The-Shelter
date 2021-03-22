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
	if (Player && Player->DamageCollision == OtherComp) {
		if (Player->IsPlayerOwner) {
			if (AreaType != 3) { //Не в двери выхода шелтора
				if (AreaType == 2 && !(Player->GS->IsVentilationPlayed))
					return;

				if (Player->GI->bIsEnabledPrompt)
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
						Player->UserView->E_Mark->SetVisibility(ESlateVisibility::Visible);
						Player->UserView->PropmptTextArea->SetText(AreaOpenAndCanEscape);
						
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
							if (Player->GI->bIsEnabledPrompt)
								Player->UserView->PropmptTextArea->SetVisibility(ESlateVisibility::Visible);
							//Player->UserView->EscapeText->SetVisibility(ESlateVisibility::Visible);

						}
						else {
							Player->UserView->PropmptTextArea->SetText(AreaNotAvaliable);
							if (Player->GI->bIsEnabledPrompt)
								Player->UserView->PropmptTextArea->SetVisibility(ESlateVisibility::Visible);
						}
					}
					else {
						Player->UserView->PropmptTextArea->SetText(AreaClose);
						if (Player->GI->bIsEnabledPrompt)
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
	if (Player && Player->DamageCollision == OtherComp) {
		if (Player->IsPlayerOwner) {
			if (AreaType != 3) { //Не в двери выхода шелтора
				if (AreaType == 2 && !(Player->GS->IsVentilationPlayed))
					return;

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
				if (Player->GI->bIsEnabledPrompt)
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
				if (!Player->LastInteractiveItem && Player->UserView)
					Player->UserView->E_Mark->SetVisibility(ESlateVisibility::Hidden);
				if (Player->GI->bIsEnabledPrompt && Player->UserView)
					Player->UserView->PropmptTextArea->SetVisibility(ESlateVisibility::Hidden);
			}
		}
	}
}

void AAreaCollision::PressedEAreaCollision(AChel* Player) {
	if (!Player->bInEscMenu && Player->bCanWalkingAndWatching) {
		switch (AreaType)
		{
			case 0: //канализация
			{
				if (Player->GS->AreaAvaliables[AreaType])
				{
					Player->MainExis_Ventilacia->Mesh->SetRenderCustomDepth(false);
					Player->MainExis_Ventilacia->Mesh->MarkRenderStateDirty();
					Player->MainExis_Shelter->Mesh->SetRenderCustomDepth(false);
					Player->MainExis_Shelter->Mesh->MarkRenderStateDirty();
					Player->MainExis_Canalizacia->Mesh->SetRenderCustomDepth(false);
					Player->MainExis_Canalizacia->Mesh->MarkRenderStateDirty();
					Player->UserView->RemoveFromParent();
					Player->PlayerEscape(AreaType);
				}
				else if (Player->DoesHave[AreaType] && Player->GS->IsCanalizaciaAvaliable && !Player->GS->AreaAvaliables[AreaType])
				{
					Player->UserView->PB_Opening->SetVisibility(ESlateVisibility::Visible);
					Player->UserView->TimeLeft->SetVisibility(ESlateVisibility::Visible);
					Player->UserView->PlayAnimation(Player->UserView->CanalizaciaAnim);
				}
				break;
			}
			case 1: //замочная скважина шелтора
			{
				if (Player->DoesHave[AreaType] && !Player->GS->AreaAvaliables[AreaType] && Player->GS->IsShelterAvaliable)
				{
					Player->UserView->PB_Opening->SetVisibility(ESlateVisibility::Visible);
					Player->UserView->TimeLeft->SetVisibility(ESlateVisibility::Visible);
					Player->UserView->PlayAnimation(Player->UserView->ShelterAnim);
				}
				break;
			}
			case 2: //вентиляция
			{
				if (!(Player->GS->IsVentilationPlayed))
					return;

				if (Player->GS->AreaAvaliables[AreaType])
				{
					Player->MainExis_Ventilacia->Mesh->SetRenderCustomDepth(false);
					Player->MainExis_Ventilacia->Mesh->MarkRenderStateDirty();
					Player->MainExis_Shelter->Mesh->SetRenderCustomDepth(false);
					Player->MainExis_Shelter->Mesh->MarkRenderStateDirty();
					Player->MainExis_Canalizacia->Mesh->SetRenderCustomDepth(false);
					Player->MainExis_Canalizacia->Mesh->MarkRenderStateDirty();
					Player->UserView->RemoveFromParent();
					Player->PlayerEscape(AreaType);

				}
				else if (Player->DoesHave[AreaType] && Player->GS->IsVentilaciaAvaliable && !Player->GS->AreaAvaliables[AreaType])
				{
					Player->UserView->PB_Opening->SetVisibility(ESlateVisibility::Visible);
					Player->UserView->TimeLeft->SetVisibility(ESlateVisibility::Visible);
					Player->UserView->PlayAnimation(Player->UserView->VentilaciaAnim);
				}
				break;
			}
			case 3: //выход шелтора(сама дверь)
			{
				if (Player->GS->AreaAvaliables[1] && !Player->GS->AreaClosed[1]) {
					Player->MainExis_Ventilacia->Mesh->SetRenderCustomDepth(false);
					Player->MainExis_Ventilacia->Mesh->MarkRenderStateDirty();
					Player->MainExis_Shelter->Mesh->SetRenderCustomDepth(false);
					Player->MainExis_Shelter->Mesh->MarkRenderStateDirty();
					Player->MainExis_Canalizacia->Mesh->SetRenderCustomDepth(false);
					Player->MainExis_Canalizacia->Mesh->MarkRenderStateDirty();
					Player->UserView->RemoveFromParent();
					Player->PlayerEscape(1);
				}
			}
		}
	}
}


