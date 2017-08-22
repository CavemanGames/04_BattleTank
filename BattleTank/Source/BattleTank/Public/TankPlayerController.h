// Caveman Games Copyright 2017

#pragma once

#include "Engine/World.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;
/**
 * Responsible for helping the player aim
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Tank")
		void FoundAimingComponent(UTankAimingComponent* AimCompRef);

public:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	
	//Start the Tank moving the Barrel
	void AimTowardsCrosshair();

	int GetAmmopBullets();
	void SetAmmopBullets(int NewAmmoBulletsValue);

private:
	UPROPERTY(EditDefaultsOnly)
		float CrosshairXLocation = 0.5;
	UPROPERTY(EditDefaultsOnly)
		float CrosshairYLocation = 0.33333;
	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 1000000.0f;
	UPROPERTY(EditDefaultsOnly)
		int AmmoBullets = 3;

	UTankAimingComponent* AimingComponent;

	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
};
