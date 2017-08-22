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

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	void ApplySidewaysForce();

private:
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	void DriveTrack();

	float CurrentThrottle = 0.f;

public:

	// Set a Throttle between -1 and +1
	UFUNCTION(BlueprintCallable, Category="Tank")
		void SetThrottle(float Throttle);
	
	// Max Force per Track, in Newtons Force
	UPROPERTY(EditDefaultsOnly, Category = "Throttle")
		float TrackMaxDrivingForce = 40000000.f;
};
