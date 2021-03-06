// Caveman Games Copyright 2017

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Tank), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 is max downward speed, and 1 is max up movement
	void Elevate(float RelativeSpeed);
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MaxDegressPerSecond = 10.f;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MaxElevation = 40.f;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MinElevation = 0.f;
};
