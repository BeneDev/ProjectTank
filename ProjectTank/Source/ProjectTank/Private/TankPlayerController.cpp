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

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& outHitLocation) const
{
	// Get the positino of the crosshair in the viewport
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D CrosshairScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	FVector LookDirection;
	if (GetLookDirection(CrosshairScreenLocation, LookDirection))
	{
		// Shoot Linetrace through the point and check if something is hit
		if (GetLookVectorHitLocation(outHitLocation, LookDirection))
		{
			return true;
		}
	}
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;

	// Deproject the crosshairScreen location to world coordinates
	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection))
	{
		return true;
	}
	return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector& outHitLocation, FVector LookDirection) const
{
	FHitResult HitResult;
	FVector StartPosition = PlayerCameraManager->GetCameraLocation();
	FVector EndPosition = StartPosition + LookDirection * LineTraceRange;
	if(GetWorld()->LineTraceSingleByChannel(HitResult, StartPosition, EndPosition, ECollisionChannel::ECC_Visibility))
	{
		outHitLocation = HitResult.Location;
		return true;
	}
	outHitLocation = FVector(0);
	return false;
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("Linetrace hits landscape at: %s"), *HitLocation.ToString());
	}

	// Aim at the crosshair
}

