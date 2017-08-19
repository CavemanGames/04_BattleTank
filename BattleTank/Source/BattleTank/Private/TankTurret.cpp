// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"


void UTankTurret::Rotation(float RelativeSpeed)
{
	float ClampedRotation = FMath::Clamp<float>(RelativeSpeed, -1, 1);

	float RotationChange = ClampedRotation * MaxRotationPerSecond * GetWorld()->DeltaTimeSeconds;
	float RawNewRotation = RelativeRotation.Yaw + RotationChange;

	SetRelativeRotation(FRotator(0.f, RawNewRotation, 0.f));
}

