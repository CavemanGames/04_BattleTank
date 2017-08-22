// Caveman Games Copyright 2017

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Tank), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
protected:
	UTankTrack();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

public:

	// Set a Throttle between -1 and +1
	UFUNCTION(BlueprintCallable, Category="Tank")
	void SetThrottle(float Throttle);
	
	// Max Force per Track, in Newtons Force
	UPROPERTY(EditDefaultsOnly, Category = "Throttle")
		float TrackMaxDrivingForce = 40000.f;
};
