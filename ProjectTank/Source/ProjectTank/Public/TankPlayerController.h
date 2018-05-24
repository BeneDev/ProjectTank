// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTTANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
public:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	// Get the tank which is controlled by the tank player controller
	ATank* GetControlledTank() const;

	// Aims the barrel in a way, so a shot would hit this target in the world
	void AimTowardsCrosshair();

	// Gets the hit location in the world, you linetrace through the crosshair. True if landscape is hit.
	bool GetSightRayHitLocation(FVector& outHitLocation) const;

	// Get the absolute look direction of the player
	bool GetLoockDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5;
	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.333333;
	
};
