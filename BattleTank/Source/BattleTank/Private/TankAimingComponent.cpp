// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"

#define OUT

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }

	FVector OutLaunchVelicity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, OUT OutLaunchVelicity, StartLocation, HitLocation, LaunchSpeed, ESuggestProjVelocityTraceOption::TraceFullPath);
	// Calculate the OutLaunchVelocity
	if (bHaveAimSolution)
	{
		FVector AimDirection = OutLaunchVelicity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		UE_LOG(LogTemp, Warning, TEXT("Aiming at %s"), *AimDirection.ToString());
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// work-out diference between current barrel rotation and AimDirection
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotator;
		
	Barrel->Elevate(5.f); //TODO Remove magic number
}

