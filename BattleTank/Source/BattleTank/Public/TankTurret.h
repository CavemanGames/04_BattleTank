// Caveman Games Copyright 2017

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

UCLASS(ClassGroup = (Tank), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Rotation(float RelativeSpeed);
	
private:
	UPROPERTY(EditDefaultsOnly)
		float MaxRotationPerSecond = 25.f;
	
};
