// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"
#include <Kismet/GameplayStatics.h>


void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank) {
		Tank->HandleDestruction();

		if (ToonTanksPlayerController) {
			ToonTanksPlayerController->SetPlayerEnabledState(false);
		}

		GameOver(false);
	}

	if (ATower* DestroyedTower = Cast<ATower>(DeadActor)) {
		DestroyedTower->HandleDestruction();
		TargetTowersCount -= 1;

		if (TargetTowersCount == 0) {
			GameOver(true);
		}
	}
}

void AToonTanksGameMode::HandleGameStart()
{
	TargetTowersCount = GetTargetTowerCount();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();

	if (ToonTanksPlayerController) {
		ToonTanksPlayerController->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableTimer;

		/// <summary>
		/// This is another version of a timer function that is called after a certain amount of time.
		/// Another version of this is implemeneted in ATower::BeginPlay -> line 26.
		/// It simply takes an object to bind to which is ToonTanksPlayerController,
		/// Then we are setting that classes method we want to run which is AToonTanksPlayerController::SetPlayerEnabledState,
		/// and then we are passing in the argument for that method which in our case is true -> so it will be SetPlayerEnabledState(true)
		/// </summary>
		FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
			ToonTanksPlayerController,
			&AToonTanksPlayerController::SetPlayerEnabledState,
			true
			);

		/// <summary>
		/// Another version of this is implemeneted in ATower::BeginPlay -> line 26. So go there for more info
		/// </summary>
		GetWorldTimerManager().SetTimer(
			PlayerEnableTimer,
			PlayerEnableTimerDelegate,
			StartGameDelay,
			false
		);
	}
}

/// <summary>
/// This function will take an array we create (Towers) and populate it with the ammount of instances
/// of the tower that currently exists in the game
/// </summary>
/// <returns>Towers.Num()</returns>
int32 AToonTanksGameMode::GetTargetTowerCount()
{
	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);

	return Towers.Num();
}
