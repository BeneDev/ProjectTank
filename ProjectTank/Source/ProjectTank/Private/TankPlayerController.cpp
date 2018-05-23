// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "ProjectTank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ATank* posessedTank = GetControlledTank();
	if (posessedTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController posessing %s"), *posessedTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not posessing a Tank."));
	}
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

