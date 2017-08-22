// Caveman Games Copyright 2017

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for Aiming States
UENUM()
enum class EFiringStates : uint8
{
	Reloading,
	Aiming,
	Locked
};

// Forward Declaration
class UTankBarrel; 
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Tank), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable, category = "Tank")
		void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	void AimAt(FVector HitLocation);

	UTankTurret* GetTurret() const;

	UTankBarrel* GetBarrel() const;

	UFUNCTION(BlueprintCallable, Category = "Tank")
	void Fire();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Tank")
		EFiringStates FiringStates = EFiringStates::Reloading;

private:

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	FVector AimDirection;
	
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 4000.0f; // Sensible starting value of 1000 m/s

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTimeInSeconds = 3.f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint;

	double LastFireTime = 0.0;

	void MoveBarrelTowards(FVector AimDirectionToSet);

	bool IsBarrelMoving();
};
