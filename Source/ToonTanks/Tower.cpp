// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include <Kismet/GameplayStatics.h>
#include <TimerManager.h>

void ATower::BeginPlay()
{
	Super::BeginPlay();

	// We need to get the Tank Pawn
	// As we have the same problem as in Tank.cpp we need to use casting
	// as we need an game object that has a specific class
	// Tank is a child of type APawn as it inherits from it
	// but as a subtype (or child) of APawn we can use CASTING to convert that into APawn
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	// This sets a timers for a specific function to run (even in a loop)
	// First we provide FTimerHandle instance
	// then it accepts a class to bind which is this class
	// then we pass a function that we want to run
	// after that a rate is passed to symbolize how often should the function run (if we pass two, the function will run every 2 seconds)
	// boolean value to say if the function should loop or not (if false, the function will simply run once after 2 seconds)
	GetWorldTimerManager().SetTimer(
		FireRateTimerHandle,
		this,
		&ATower::CheckFireCondition,
		FireRate,
		true);
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Here we are rotation the tower's turret
	if (isTankInRange()) {
		RotateTurret(Tank->GetActorLocation());
	}
}

/// <summary>
/// This function serves as an inherited contstructor of sort
/// The first implementation is in the BasePawn::HandleDestruction
/// This is calling the Super method to execute the code in BasePawn::HandleDestruction
/// and on top of that it is going to call Destroy method and destroy this class.
/// Please check Function AToonTanksGameMode::ActorDied for more info.
/// </summary>
void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

// Here we check whether the tank is in the fire range
// If it is, the Turret will start to Fire
// this function is run in a timer - see lines 26 - 32 so it runs in a loop every 2 seconds
void ATower::CheckFireCondition()
{
	// Here we are triggering the fire
	if (Tank) {
		if (isTankInRange() && Tank->isTankAlive) {
			Fire();
		}
	}
}


bool ATower::isTankInRange()
{
	if (Tank) {
		// We need to find the distance to the tank
		// We also need to check if tank is in range
		// is the tank is in range, we need to rotate the turret
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());

		if (FireRange > Distance) {
			return true;
		}
		else {
			return false;
		}
	}
	else return false;
}
