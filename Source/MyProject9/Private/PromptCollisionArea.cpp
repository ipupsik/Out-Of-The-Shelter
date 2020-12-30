// Fill out your copyright notice in the Description page of Project Settings.


#include "PromptCollisionArea.h"

// Sets default values
APromptCollisionArea::APromptCollisionArea()
{
	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	Collision->SetupAttachment(RootComponent);

	Collision->OnComponentBeginOverlap.AddDynamic(this, &APromptCollisionArea::OnOverlapBegin);
	Collision->OnComponentEndOverlap.AddDynamic(this, &APromptCollisionArea::OnOverlapEnd);

	PromptedItems.Init(nullptr,0);
}

void APromptCollisionArea::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult) {
	UE_LOG(LogTemp, Warning, TEXT("SomebodyBeginOverlap"));
	AChel* Player = Cast<AChel>(OtherActor);
	if (Player) {
		if (Player == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)) {
			for(auto& item : PromptedItems)
			{
				item->Mesh->SetCustomDepthStencilValue(2);
				Player->AddTargetArrow(item);
			}
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("NotAMainPalyerStartOverlap"));
		}
	}
}

void APromptCollisionArea::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("SomebodyEndOverlap"));
	AChel* Player = Cast<AChel>(OtherActor);
	if (Player) {
		if (Player == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)) {
			for(auto& item : PromptedItems)
			{
				item->Mesh->SetCustomDepthStencilValue(0);
				Player->RemoveTargetArrow(item);
			}
		}
	}
}