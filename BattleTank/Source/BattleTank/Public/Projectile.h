// Caveman Games Copyright 2017

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class UParticleSystemComponent;
class UStaticMeshComponent;

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
		void OnTimerEnd();
	
	UProjectileMovementComponent* ProjectileMovement = nullptr;

	UPROPERTY(EditAnywhere, Category = "Components", meta = (AllowPrivateAccess = true))
		UStaticMeshComponent* CollisionMesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Components", meta = (AllowPrivateAccess = true))
		UParticleSystemComponent* LaunchBlast = nullptr;

	UPROPERTY(EditAnywhere, Category = "Components", meta = (AllowPrivateAccess = true))
		UParticleSystemComponent* ImpactBlast = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float TimeDelayToParticles = 5.f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void LaunchProjectile(float Speed);
	

private:
	FTimerHandle Delay;
};
