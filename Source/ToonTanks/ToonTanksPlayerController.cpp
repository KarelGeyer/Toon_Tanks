// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksPlayerController.h"

void AToonTanksPlayerController::SetPlayerEnabledState(bool bPlayerEnabled)
{
	// This will make sure that our chararcter will not be able to move bPlayerEnabled is false
	if (bPlayerEnabled) {
		GetPawn()->EnableInput(this);
	}
	else {
		GetPawn()->DisableInput(this);
	}

	bShowMouseCursor = bPlayerEnabled;
}
