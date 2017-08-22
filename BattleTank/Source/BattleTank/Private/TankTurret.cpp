// Caveman Games Copyright 2017

#include "TankTurret.h"


void UTankTurret::Rotation(float RelativeSpeed)
{
	float ClampedRotation = FMath::Clamp<float>(RelativeSpeed, -1, 1);

	float RotationChange = ClampedRotation * MaxRotationPerSecond * GetWorld()->DeltaTimeSeconds;
	float RawNewRotation = RelativeRotation.Yaw + RotationChange;

	SetRelativeRotation(FRotator(0.f, RawNewRotation, 0.f));
}

