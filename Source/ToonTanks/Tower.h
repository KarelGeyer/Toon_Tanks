// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 *
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

private:
	UPROPERTY(VisibleAnywhere, Category = "Base Props")
		float FireRange = 1200.f;

	class ATank* Tank;

	// This is engine built in function to manage timers
	// can be used for instance to run a specific function
	// every for example few seconds or minutes
	FTimerHandle FireRateTimerHandle;
	float FireRate = 2.f;

	void CheckFireCondition();
	bool isTankInRange();
};
