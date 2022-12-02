// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/// <summary>
/// This class is goign to take care of global actions and functionalities such
/// character dying, starting the game or ending the game et cetra
/// </summary>
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	/// <summary>
	/// This function is called when Actor is supposed to die. It is called from UHealtComponent::DamageTaken function
	/// </summary>
	void ActorDied(AActor* DeadActor);

protected:
	virtual void BeginPlay() override;

	/// <summary>
	/// This function is marked as BlueprintImplementable which means its logic is going to be implemented in blueprints
	/// and its only going to be called from C++.
	/// Open blueprints for ToonTanksGameMode and see Event Start Game
	/// </summary>
	UFUNCTION(BlueprintImplementableEvent)
		void StartGame();

	/// <summary>
	/// Open blueprints for ToonTanksGameMode and see Event Game Over
	/// </summary>
	UFUNCTION(BlueprintImplementableEvent)
		void GameOver(bool bWonGame);
private:

	class ATank* Tank;
	class AToonTanksPlayerController* ToonTanksPlayerController;

	int32 TargetTowersCount = 0;
	float StartGameDelay = 3.f;

	/// <summary>
	/// This function is called when Actor is supposed to die. It is called from UHealtComponent::DamageTaken function
	/// </summary>
	void HandleGameStart();

	int32 GetTargetTowerCount();

};
