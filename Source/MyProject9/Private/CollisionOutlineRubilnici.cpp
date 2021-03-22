// Fill out your copyright notice in the Description page of Project Settings.


#include "CollisionOutlineRubilnici.h"
#include "Chel.h"
#include "BP_VentilaciaRubilnick.h"

// Sets default values
ACollisionOutlineRubilnici::ACollisionOutlineRubilnici()
{
	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	Collision->SetupAttachment(RootComponent);

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ACollisionOutlineRubilnici::OnOverlapBegin);
	Collision->OnComponentEndOverlap.AddDynamic(this, &ACollisionOutlineRubilnici::OnOverlapEnd);

	IsEnabled = true;

}


void ACollisionOutlineRubilnici::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (IsEnabled) {
		AChel* Player = Cast<AChel>(OtherActor);
		if (Player && Player->GS->IsVentilationPlayed) {
			if (Player->IsPlayerOwner) {
				Player->IsInCollisionOutlRubilnici = true;
				TArray<AActor*> AllRubilnics;
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABP_VentilaciaRubilnick::StaticClass(), AllRubilnics);
				for (auto& it : AllRubilnics) {
					ABP_VentilaciaRubilnick* CurRubilnic = Cast<ABP_VentilaciaRubilnick>(it);
					if (CurRubilnic) {
						if (!CurRubilnic->Item->bRenderCustomDepth && CurRubilnic->bCanInterract && CurRubilnic->IsEnableWhen3Player) {
							CurRubilnic->Item->SetRenderCustomDepth(true);
							CurRubilnic->Item->MarkRenderStateDirty();
						}					
					}
				}
			}
		}
	}

}

void ACollisionOutlineRubilnici::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex) {
	if (IsEnabled) {
		AChel* Player = Cast<AChel>(OtherActor);
		if (Player && Player->GS->IsVentilationPlayed) {
			if (Player->IsPlayerOwner) {
				Player->IsInCollisionOutlRubilnici = false;
				TArray<AActor*> AllRubilnics;
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABP_VentilaciaRubilnick::StaticClass(), AllRubilnics);
				for (auto& it : AllRubilnics) {
					ABP_VentilaciaRubilnick* CurRubilnic = Cast<ABP_VentilaciaRubilnick>(it);
					if (CurRubilnic->Item->bRenderCustomDepth && CurRubilnic->IsEnableWhen3Player) {
						CurRubilnic->Item->SetRenderCustomDepth(false);
						CurRubilnic->Item->MarkRenderStateDirty();
					}
				}
			}
		}
	}
}