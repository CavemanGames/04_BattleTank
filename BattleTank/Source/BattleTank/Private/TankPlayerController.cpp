// Caveman Games Copyright 2017

#include "TankPlayerController.h"
#include "TankAimingComponent.h"

#define OUT

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(AimingComponent)) { return; }

	FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; }

	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	FVector HitLocation; // Out parameter

	bool bGotHitLocation = GetSightRayHitLocation(HitLocation);

	if (bGotHitLocation) // Has "side-efect", is going to line trace
	{
		AimingComponent->AimAt(HitLocation);
	}
}

void ATankPlayerController::SetAmmopBullets(int NewAmmoBulletsValue)
{
	AmmoBullets = NewAmmoBulletsValue;
}

int ATankPlayerController::GetAmmopBullets()
{
	return AmmoBullets;
}

// Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	// Find the crosshair position in pixels coordenates
	int32 ViewportSizeX, ViewportSizeY;

	GetViewportSize(OUT ViewportSizeX, OUT ViewportSizeY);

	FVector2D ScreenLocation = FVector2D((ViewportSizeX * CrosshairXLocation), (ViewportSizeY * CrosshairYLocation));

	FVector LookDirection;

	// "De-preoject" The Screen position of the crosshair to a world direction
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line-trace along that look direction, and see what we hit (up to max range)
		return GetLookVectorHitLocation(LookDirection, OUT OutHitLocation);
	}

	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const
{
	FVector TankWorldLocation; // To be discarted
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, OUT TankWorldLocation, OUT LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	FVector LineTraceStart = PlayerCameraManager->GetCameraLocation();
	FVector LineTraceEnd = LineTraceStart + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(OUT HitResult, LineTraceStart, LineTraceEnd, ECollisionChannel::ECC_Visibility)) // LineTrace Succeeds
	{
		HitLocation = HitResult.Location;
		return true;
	}

	return false;
}
