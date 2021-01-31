// Fill out your copyright notice in the Description page of Project Settings.


#include "Spectator.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Chel.h"
// Sets default values
ASpectator::ASpectator()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("PawnMovement"));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArm);

	//Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	//Collision->SetupAttachment(CameraComp);

	Sensetivity = 1.0f;
	IsKilled = false;
	IsFreeCam = false;
}

// Called when the game starts or when spawned
void ASpectator::BeginPlay()
{
	Super::BeginPlay();
	
	GS = Cast<AGS>(GetWorld()->GetGameState());
	if (GetLocalRole() != ROLE_Authority)
	{
		Sensetivity = GetWorld()->GetGameInstance<UGI>()->Sensetivity;
		TArray<UUserWidget*>Widgets;
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), Widgets, SpectatorWidget_class);
		if (Widgets.Num() == 0)
			CreateWidget(GetWorld(), SpectatorWidget_class)->AddToViewport();
	}
}

void ASpectator::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(ASpectator, Player, COND_OwnerOnly);
	DOREPLIFETIME(ASpectator, IsFreeCam);
	DOREPLIFETIME(ASpectator, IsKilled);
}

// Called every frame
void ASpectator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Player) {
		if (!IsFreeCam) {
			FVector NewRotation = Player->GetActorLocation();
			NewRotation.Z = Player->CameraComp->GetComponentLocation().Z;
			SetActorLocation(NewRotation);
		}
	}
}

void ASpectator::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);


	TargetArmNotFreeCamera_Multicast();
}

void ASpectator::TargetArmFreeCamera_Implementation()
{
	IsFreeCam = true;
	SpringArm->TargetArmLength = 0;
}

bool ASpectator::TargetArmFreeCamera_Validate()
{
	return true;
}

void ASpectator::TargetArmNotFreeCamera_Multicast_Implementation()
{
	IsFreeCam = false;
	SpringArm->TargetArmLength = 300;
}

void ASpectator::TargetArmNotFreeCamera_Server_Implementation()
{
	IsFreeCam = false;
	TargetArmNotFreeCamera_Multicast();
}

bool ASpectator::TargetArmNotFreeCamera_Server_Validate()
{
	return true;
}

void ASpectator::GoToFreeCamera()
{
	if (!IsFreeCam) {
		IsFreeCam = true;
		SpringArm->TargetArmLength = 0;
		TargetArmFreeCamera();
	}
	else
	{
		IsFreeCam = false;
		SpringArm->TargetArmLength = 300;
		TargetArmNotFreeCamera_Server();
	}
}

// Called to bind functionality to input
void ASpectator::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("LookUp", this, &ASpectator::LookUp);
	PlayerInputComponent->BindAxis("LookRight", this, &ASpectator::LookRight);
	PlayerInputComponent->BindAxis("GoForward", this, &ASpectator::GoForward);
	PlayerInputComponent->BindAxis("GoRight", this, &ASpectator::GoRight);

	PlayerInputComponent->BindAction("UpdateSpectating_Left", IE_Pressed, this, &ASpectator::ChangeSpecLeft);
	PlayerInputComponent->BindAction("UpdateSpectating_Right", IE_Pressed, this, &ASpectator::ChangeSpecRight);
	PlayerInputComponent->BindAction("GoToFreeCamera", IE_Pressed, this, &ASpectator::GoToFreeCamera);
}

void ASpectator::GoRight(float input)
{
	if (IsFreeCam && input != 0.0f)
	{
		AddMovementInput(CameraComp->GetRightVector(), input * Sensetivity);
	}
}

void ASpectator::GoForward(float input)
{
	if (IsFreeCam && input != 0.0f)
	{
		AddMovementInput(CameraComp->GetForwardVector(), input * Sensetivity);
	}
}

void ASpectator::LookUp(float input)
{
	if (input != 0.0f) {
		input *= Sensetivity;
		input *= -1;
		AddControllerPitchInput(input);
	}
}


void ASpectator::LookRight(float input)
{
	if (input != 0.0f) {
		input *= Sensetivity;
		AddControllerYawInput(input);
	}
}

void ASpectator::ChangeSpecRight()
{
	if (!IsFreeCam)
		UpdateSpectating_Right();
}

void ASpectator::ChangeSpecLeft()
{
	if (!IsFreeCam)
		UpdateSpectating_Left();
}

void ASpectator::UpdateSpectating_Left_Implementation()
{
	int32 MaxPlayersCount = GetWorld()->GetGameInstance<UGI>()->MaxPlayersCount;
	int iteration = 0;
	for (iteration = Layer; iteration < MaxPlayersCount * (MaxPlayersCount - 2); iteration += (MaxPlayersCount - 2))
	{
		if (GS->Spectators[iteration]->Index == Index)
			break;
	}
	iteration -= (MaxPlayersCount - 2);
	while (true)
	{
		if (iteration < 0)
		{
			iteration += MaxPlayersCount * (MaxPlayersCount - 2);
		}
		if (!GS->Spectators[iteration]->IsKilled)
		{
			GetController()->Possess(GS->Spectators[iteration]);
			break;
		}
		iteration -= MaxPlayersCount - 2;
	}
}

bool ASpectator::UpdateSpectating_Left_Validate()
{
	return true;
}


void ASpectator::UpdateSpectating_Right_Implementation()
{
	int32 MaxPlayersCount = GetWorld()->GetGameInstance<UGI>()->MaxPlayersCount;
	int iteration = 0;
	UE_LOG(LogTemp, Warning, TEXT("Count - %d"), MaxPlayersCount);
	for (iteration = Layer; iteration < MaxPlayersCount * (MaxPlayersCount - 2); iteration += (MaxPlayersCount - 2))
	{
		if (GS->Spectators[iteration]->Index == Index)
			break;
	}
	iteration += MaxPlayersCount - 2;
	while (true)
	{
		if (iteration >= MaxPlayersCount * (MaxPlayersCount - 2))
		{
			iteration -= MaxPlayersCount * (MaxPlayersCount - 2);
		}
		if (!GS->Spectators[iteration]->IsKilled)
		{
			GetController()->Possess(GS->Spectators[iteration]);
			break;
		}
		iteration += MaxPlayersCount - 2;
	}
}

bool ASpectator::UpdateSpectating_Right_Validate()
{
	return true;
}
