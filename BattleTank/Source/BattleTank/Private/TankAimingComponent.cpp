// Caveman Games Copyright 2017

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "EngineMinimal.h"

#define OUT

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}

void UTankAimingComponent::BeginPlay()
{
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{	
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringStates = EFiringStates::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringStates = EFiringStates::Aiming;
	}
	else
	{
		FiringStates = EFiringStates::Locked;
	}
}

void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	if (!ensure(BarrelToSet && TurretToSet)) { return; }
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel && Turret)) { return; }

	FVector OutLaunchVelicity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, OUT OutLaunchVelicity, StartLocation, HitLocation, LaunchSpeed, false, 100.f, 0.f, ESuggestProjVelocityTraceOption::DoNotTrace);
	// Calculate the OutLaunchVelocity
	if (bHaveAimSolution)
	{
		FVector AimDirection = OutLaunchVelicity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
		// No Aim solution Found
}

UTankTurret * UTankAimingComponent::GetTurret() const
{
	return Turret;
}

UTankBarrel * UTankAimingComponent::GetBarrel() const
{
	return Barrel;
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel)) { return; }
	if (!ensure(ProjectileBlueprint)) { return; }
	if (FiringStates != EFiringStates::Reloading)
	{
		//Spawn a projectile at the socket location of barrel
		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));
		projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirectionToSet)
{
	AimDirection = AimDirectionToSet;
	if (!ensure(Barrel && Turret)) { return; }
	// work-out diference between current barrel rotation and AimDirection
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotator;
		
	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotation(DeltaRotator.Yaw);
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	return !Barrel->GetForwardVector().Equals(AimDirection, 0.01f);
}

