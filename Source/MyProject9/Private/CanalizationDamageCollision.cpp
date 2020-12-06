// Fill out your copyright notice in the Description page of Project Settings.


#include "CanalizationDamageCollision.h"
#include "Kismet/GameplayStatics.h"
#include "Chel.h"
#include "CanalizationButton.h"
// Sets default values
ACanalizationDamageCollision::ACanalizationDamageCollision()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	Collision->SetupAttachment(RootComponent);

	RadiationDamageCoef = 4.0f;

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ACanalizationDamageCollision::OnOverlapBegin);
	Collision->OnComponentEndOverlap.AddDynamic(this, &ACanalizationDamageCollision::OnOverlapEnd);
}

void ACanalizationDamageCollision::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GetLocalRole() == ROLE_Authority)
	{
		UE_LOG(LogTemp, Warning, TEXT("OnBeginOverlapp"))
		Cast<AChel>(OtherActor)->CanalizationDamage = RadiationDamageCoef;
	}
}

void ACanalizationDamageCollision::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (GetLocalRole() == ROLE_Authority)
	{
		UE_LOG(LogTemp, Warning, TEXT("OnEndOverlapp"))
		Cast<AChel>(OtherActor)->CanalizationDamage = 1.0f;
	}
}


void ACanalizationDamageCollision::StopRadiation()
{
	RadiationDamageCoef = 1.0f;
	TArray<AActor*>Players;
	Collision->GetOverlappingActors(Players, AChel::StaticClass());
	for (auto& it : Players)
	{
		Cast<AChel>(it)->CanalizationDamage = RadiationDamageCoef;
	}

	FTimerHandle FuzeTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(FuzeTimerHandle, this, &ACanalizationDamageCollision::RefreshRadiation, 15.0f, false);

	TArray<AActor*>Buttons;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACanalizationButton::StaticClass(), Buttons);

	for (auto& it : Buttons)
	{
		Cast<ACanalizationButton>(it)->DoesRefresh = false;
	}
}

void ACanalizationDamageCollision::RefreshRadiation()
{
	GetWorld()->GetGameState<AGS>()->CurrentButtonCount = 0;
	RadiationDamageCoef = 4.0f;
	TArray<AActor*>Players;
	Collision->GetOverlappingActors(Players, AChel::StaticClass());
	for (auto& it : Players)
	{
		Cast<AChel>(it)->CanalizationDamage = RadiationDamageCoef;
	}

	TArray<AActor*>Buttons;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACanalizationButton::StaticClass(), Buttons);

	for (auto& it : Buttons)
	{
		ACanalizationButton* Button = Cast<ACanalizationButton>(it);
		Button->DoesRefresh = true;
		Button->Close();
	}
}
