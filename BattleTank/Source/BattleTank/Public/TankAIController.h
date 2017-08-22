// Caveman Games Copyright 2017

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float AcceptanceRadius = 8000.f;
};
