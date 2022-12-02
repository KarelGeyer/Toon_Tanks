// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	void HandleDestruction();

protected:
	// Common function for both the Tank turret (the upper part of the tank) and the enemy Turrets
	// As they both need it to rotate (they need to aim) to a specific location
	// The Parameter for this function is the target location our Pawns need to rotate to
	void RotateTurret(FVector LookAtTarget);
	// Similarly we are going to create a function that can be
	// used by all child classes to FIRE
	void Fire();

private:
	// In here we do not import the headers as it takes up memory and we declare packages with class -> see forward declaration
	// The header does not need to know the components properties or size or anything, it just needs to be declared here so we can work wit it
	// So importing the header file for UCapsuleComponent would be bad practice as it required memory
	// So if you need to declare something that needs a header, in here only use CLASS and import the package in cpp file
	UPROPERTY(VisibleAnywhere, Category = "Components", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UCapsuleComponent* CapsuleComp; // Capsule component is just a component for collision, it does not have a shape or anything
	// UStaticMeshComponent is already part and inherited (? most likely) so we do not need to use forward declaration
	UPROPERTY(VisibleAnywhere, Category = "Components", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* BaseMesh; // This is a mesh component to wich we can give some design
	UPROPERTY(VisibleAnywhere, Category = "Components", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleAnywhere, Category = "Components", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
		TSubclassOf<class AProjectile> ProjectileClass;

	/// <summary>
	/// This way we can add particles and effect to our Pawns, see in blueprints
	/// </summary>
	UPROPERTY(EditAnywhere, Category = "Combat")
		UParticleSystem* DeathParticles;

	UPROPERTY(EditAnywhere, Category = "Combat")
		USoundBase* DeathSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
		TSubclassOf<class UCameraShakeBase> DeathCameraShakeClass;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
