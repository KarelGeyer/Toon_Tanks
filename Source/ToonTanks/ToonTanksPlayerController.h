// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ToonTanksPlayerController.generated.h"

/// <summary>
/// This class going to allow us to create our own Player controller so we can
/// display for instance crosshair mouse cursor or disable mouse cursou entirely.
/// We can also disable/enable all input on the player char - TANK
/// </summary>
UCLASS()
class TOONTANKS_API AToonTanksPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	void SetPlayerEnabledState(bool bPlayerEnabled);
};
