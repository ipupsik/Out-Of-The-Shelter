// Fill out your copyright notice in the Description page of Project Settings.


#include "QAbility_ChelDetector.h"
#include "InteractiveCache.h"
#include "Chel.h"
#include "Components/PoseableMeshComponent.h"
#include "CoreItem.h"

FVector UQAbility_ChelDetector::GetCacheScale3D(int32 CacheIndex)
{
	AGS* MyGS = GetWorld()->GetGameState<AGS>();
	return MyGS->ChelDetectorTransform[MyGS->Caches[CacheIndex]->CacheIndex].GetScale3D();
}

FRotator UQAbility_ChelDetector::GetCacheRotation(int32 CacheIndex)
{
	AGS* MyGS = GetWorld()->GetGameState<AGS>();
	return FRotator(MyGS->ChelDetectorTransform[MyGS->Caches[CacheIndex]->CacheIndex].GetRotation());
}

FVector UQAbility_ChelDetector::GetCacheLocation(int32 CacheIndex)
{
	AGS* MyGS = GetWorld()->GetGameState<AGS>();
	return MyGS->ChelDetectorTransform[MyGS->Caches[CacheIndex]->CacheIndex].GetLocation();
}

bool UQAbility_ChelDetector::UseAbilityClient(AChel* Player)
{
	Player->RentgentOnSound();
	for (auto& it : Player->PlayersArray)
	{
		if (!it->IsPlayerOwner) {
			UE_LOG(LogTemp, Warning, TEXT("lla"))
				it->PoseableMeshComp->SetRenderCustomDepth(true);
			it->PoseableMeshComp->MarkRenderStateDirty();
		}
	}
	Player->IsQAbilityUsing = true;
	Player->QAbilityTimer = FTimerHandle();
	TmpPlayer = Player;
	GetWorld()->GetTimerManager().SetTimer(Player->QAbilityTimer, this, &UQAbility_ChelDetector::DeUseAbilityClient, Duration, false);
	return false;
}

void UQAbility_ChelDetector::DeUseAbilityClient()
{
	TmpPlayer->RentgentOffSound();
	for (auto& it : TmpPlayer->PlayersArray)
	{
		if (!it->IsPlayerOwner) {
			it->PoseableMeshComp->SetRenderCustomDepth(false);
			it->PoseableMeshComp->MarkRenderStateDirty();
		}
	}
	if (TmpPlayer->IsQAbilityUsing) {
		TmpPlayer->IsQAbilityUsing = false;
		TmpPlayer->IsQAbilityRefreshing = true;
		TmpPlayer->QAbilityTimer = FTimerHandle();
		GetWorld()->GetTimerManager().SetTimer(TmpPlayer->QAbilityTimer, TmpPlayer, &AChel::QAbilityEnableAvaliable, DurationAvaliable, false);
	}
}
