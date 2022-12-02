// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 *
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank(); // This must be decleared as it is the contrusctor;

	// Called to bind functionality to input - this is used for instance to manage character movement
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool isTankAlive = true;

	void HandleDestruction();

	APlayerController* GetTankPlayerController() const { return TankPlayerController; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// With these we can create CAMERA components
	UPROPERTY(VisibleAnywhere, Category = "Camera")
		class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, Category = "Camera")
		class UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, Category = "Base Values")
		float Speed = 100.f;
	UPROPERTY(EditAnywhere, Category = "Base Values")
		float TurnRate = 60.f;

	APlayerController* TankPlayerController;

	void Move(float Value);
	void Turn(float Value);
};
