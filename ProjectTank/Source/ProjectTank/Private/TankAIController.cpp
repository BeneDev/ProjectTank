// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ATank* playerTank = GetPlayerTank();
	if (playerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("The Player controls %s"), *playerTank->GetName())
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("There is no Tank in the scene, who is controlled by a Player."))
	}
}

void ATankAIController::Tick(float DeltaTime)
{ 
	Super::Tick(DeltaTime);
	if (GetPlayerTank())
	{
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}
