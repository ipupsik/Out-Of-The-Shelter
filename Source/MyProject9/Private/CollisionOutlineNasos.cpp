// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionOutlineNasos.h"
#include "Chel.h"
#include "DezinfectorNasos.h"

// Sets default values
ACollisionOutlineNasos::ACollisionOutlineNasos()
{
	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	Collision->SetupAttachment(RootComponent);

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ACollisionOutlineNasos::OnOverlapBegin);
	Collision->OnComponentEndOverlap.AddDynamic(this, &ACollisionOutlineNasos::OnOverlapEnd);

	IsEnabled = true;
}

void ACollisionOutlineNasos::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (IsEnabled) {
		AChel* Player = Cast<AChel>(OtherActor);
		if (Player) {
			if (Player->IsPlayerOwner) {
				Player->IsInCollisionOutlNasos = true;
				TArray<AActor*> AllNasoses;
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADezinfectorNasos::StaticClass(), AllNasoses);
				for (auto& it : AllNasoses) {
					ADezinfectorNasos* CurNasos = Cast<ADezinfectorNasos>(it);
					if (CurNasos) {
						if (!CurNasos->Nasos->bRenderCustomDepth && CurNasos->bIsAvaliable) {
							CurNasos->Nasos->SetRenderCustomDepth(true);
							CurNasos->Nasos->MarkRenderStateDirty();
						}
					}
				}
			}
		}
	}

}

void ACollisionOutlineNasos::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex) {
	if (IsEnabled) {
		AChel* Player = Cast<AChel>(OtherActor);
		if (Player) {
			if (Player->IsPlayerOwner) {
				Player->IsInCollisionOutlNasos = false;
				TArray<AActor*> AllNasoses;
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADezinfectorNasos::StaticClass(), AllNasoses);
				for (auto& it : AllNasoses) {
					ADezinfectorNasos* CurNasos = Cast<ADezinfectorNasos>(it);
					if (CurNasos->Nasos->bRenderCustomDepth) {
						CurNasos->Nasos->SetRenderCustomDepth(false);
						CurNasos->Nasos->MarkRenderStateDirty();
					}
				}
			}
		}
	}
}
