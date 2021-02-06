// Fill out your copyright notice in the Description page of Project Settings.


#include "Ventil.h"
#include "Chel.h"
#include "ParticleGasCPP.h"
#include "DamageAreaCPP.h"

AVentil::AVentil() {
	Scene = CreateDefaultSubobject<USceneComponent>("Scene");
	Scene->SetupAttachment(RootComponent);

	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	Collision->SetupAttachment(Scene);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(Scene);

	IndexOwner = -1;
	TimeVentilAnim = 0.f;
}

void AVentil::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AVentil, TimeVentilAnim);
}

void AVentil::CallReverseAnimation_Implementation() {
	IndexOwner = -1;
	ChangeIndexOwner(-1);
	SetOwner(nullptr);
	RotateVentilReverse();
}

bool AVentil::CallReverseAnimation_Validate() {
	return true;
}

void AVentil::ToggleCustomDepth(bool NewIsOutliningNow, AChel* Player)
{
	if (this->IsOutliningNow != NewIsOutliningNow) {
		Mesh->SetRenderCustomDepth(NewIsOutliningNow);
		Mesh->MarkRenderStateDirty();
		this->IsOutliningNow = NewIsOutliningNow;
		if (NewIsOutliningNow == false && IndexOwner == Player->Index) {
			Player->IsSuccessOpening = false;
			Player->UserView->StopAllAnimations();
			CallReverseAnimation();
		}
	}
}

void AVentil::SetOutlineColor(int32 ColorOutline)
{
	if (bCanInterract && colorOutlineType != ColorOutline && ColorOutline != 0) {
		Mesh->SetCustomDepthStencilValue(ColorOutline);
		Mesh->MarkRenderStateDirty();
		colorOutlineType = ColorOutline;
	}
}

void AVentil::OnLineTraced(AChel* Player)
{
	if(bCanInterract)
		ToggleCustomDepth(true, Player);

	if (bCanInterract && (IndexOwner == Player->Index || IndexOwner == -1)) {
		if (Player->GI->bIsEnabledPrompt && Player->UserView->PropmptTextInterract->GetText().ToString() != PromptText.ToString())
			Player->UserView->PropmptTextInterract->SetText(PromptText);
		if (!Player->UserView->E_Mark->IsVisible()) {
			Player->UserView->E_Mark->SetVisibility(ESlateVisibility::Visible);
			if (Player->GI->bIsEnabledPrompt && !Player->UserView->PropmptTextInterract->IsVisible())
				Player->UserView->PropmptTextInterract->SetVisibility(ESlateVisibility::Visible);
		}
		SetOutlineColor(2);
	}
	else if(bCanInterract) {
		
		if (Player->UserView->E_Mark->IsVisible()) {
			Player->UserView->E_Mark->SetVisibility(ESlateVisibility::Hidden);
			if (Player->GI->bIsEnabledPrompt && Player->UserView->PropmptTextInterract->IsVisible())
				Player->UserView->PropmptTextInterract->SetVisibility(ESlateVisibility::Hidden);
		}
		SetOutlineColor(1);
	}
	else {
		if (Player->GI->bIsEnabledPrompt && Player->UserView->PropmptTextInterract->GetText().ToString() != AreaUsedText.ToString())
			Player->UserView->PropmptTextInterract->SetText(AreaUsedText);
		if (Player->UserView->E_Mark->IsVisible()) {
			Player->UserView->E_Mark->SetVisibility(ESlateVisibility::Hidden);
		}
		if (Player->GI->bIsEnabledPrompt && !Player->UserView->PropmptTextInterract->IsVisible())
			Player->UserView->PropmptTextInterract->SetVisibility(ESlateVisibility::Visible);
		ToggleCustomDepth(false, Player);
	}
}

void AVentil::PickUpEventServer(AChel * Player)
{
	IndexOwner = Player->Index;
	ChangeIndexOwner(Player->Index);
	SetOwner(Player);
	RotateVentil();
}

bool AVentil::PickUpEventClient(AChel * Player)
{
	if (bCanInterract && (IndexOwner == Player->Index || IndexOwner == -1)) {
		Player->UserView->PB_Opening->SetVisibility(ESlateVisibility::Visible);
		Player->UserView->TimeLeft->SetVisibility(ESlateVisibility::Visible);
		Player->UserView->PlayAnimation(Player->UserView->OpenAreaAnim, TimeVentilAnim);
		return true;
	}
	else
		return false;
}

void AVentil::ChangeCanInterract_Implementation(bool val) {
	if (GetLocalRole() != ROLE_Authority)
		bCanInterract = val;
}

void AVentil::ChangeIndexOwner_Implementation(int32 idx) {
	if (GetLocalRole() != ROLE_Authority) {
		IndexOwner = idx;
	}
}

void AVentil::CreateGasOnLevel() {
	//добавление текста всем игрокам
	TArray<AActor*> Chls;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AChel::StaticClass(), Chls);
	for (auto& it : Chls) {
		AChel* Plr = Cast<AChel>(it);
		if (Plr) {
			Plr->AddMessagePlayerActiveVentil(areaType, Plr->NickName);
		}
	}

	//cоздание самого газа
	UE_LOG(LogTemp, Warning, TEXT("CreateGas"));
	bCanInterract = false;
	ChangeCanInterract(false);
	IndexOwner = -1;
	ChangeIndexOwner(-1);
	SetOwner(nullptr);

	TArray<AActor*> PS_Targets;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), ATargetPoint::StaticClass(), GasAreaParticleTag, PS_Targets);

	for (auto& it : PS_Targets)
	{
		AParticleGasCPP* PSActor = GetWorld()->SpawnActor<AParticleGasCPP>(PS_Class, it->GetActorTransform());
		PSActor->areaType = areaType;
		PlaySoundGas(it->GetActorLocation());
	}

	TArray<AActor*> DamageArea_Targets;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), ATargetPoint::StaticClass(), GasAreaDamageTag, DamageArea_Targets);

	for (auto& it : DamageArea_Targets)
	{
		ADamageAreaCPP* DamageActor = GetWorld()->SpawnActor<ADamageAreaCPP>(DamageAreaClass, it->GetActorTransform());
		if (DamageActor) {
			DamageActor->areaType = areaType;
		}
	}

	FTimerHandle FuzeTimerHandle1;
	GetWorld()->GetTimerManager().SetTimer(FuzeTimerHandle1, this, &AVentil::RotateVentilReverse, 15, false);

	FTimerHandle FuzeTimerHandle2;
	GetWorld()->GetTimerManager().SetTimer(FuzeTimerHandle2, this, &AVentil::DeleteAllObjects, 21, false);
}

void AVentil::DeleteAllObjects() {
	TArray<AActor*> PS_Targets;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AParticleGasCPP::StaticClass(), PS_Targets);

	for (auto& it : PS_Targets)
	{
		if (Cast<AParticleGasCPP>(it)->areaType == areaType)
		{
			it->Destroy();
		}
	}

	TArray<AActor*> DamageArea_Targets;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADamageAreaCPP::StaticClass(), DamageArea_Targets);

	for (auto& it : DamageArea_Targets)
	{
		if (Cast<ADamageAreaCPP>(it)->areaType == areaType)
		{
			it->Destroy();
		}
	}

	bCanInterract = true;
	ChangeCanInterract(true);
}

bool AVentil::PickUpEventReleaseClient(AChel* Player) {
	if (bCanInterract) {
		Player->UserView->StopAllAnimations();
		return true;
	}
	else
		return false;
}

void AVentil::PickUpEventReleaseServer(AChel* Player) {
	IndexOwner = -1;
	ChangeIndexOwner(-1);
	SetOwner(nullptr);
	RotateVentilReverse();
}
