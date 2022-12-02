// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePawn.h"
#include "Projectile.h"
#include <Components/CapsuleComponent.h>
#include <Kismet/GameplayStatics.h>
#include <DrawDebugHelpers.h>

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// This creates a subcomponent for our BasePawn
	// CreateDefaultSubobject is a TEMPLATE so it requires a type passed in <>
	// It returns an address so we have to store it in a POINTER
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));

	// This way we make our Capsule component to be the ROOT component
	RootComponent = CapsuleComp;

	// the same way we create or mesh components
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	// this way we can attach our MESH component to the CAPSULE component
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	// same way it works for scene components
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

/// <summary>
/// This function is taking care of destroying the BasePawn Object in the game
/// 1. it is destroying the visual and sound effects
/// 2.
/// </summary>
void ABasePawn::HandleDestruction()
{
	/// <summary>
	///  This way we can spawn and show particle effects -> we are showing explosion effect
	/// </summary>
	if (DeathParticles) {
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticles, GetActorLocation(), GetActorRotation());
	}

	if (DeathSound) {
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	}

	if (DeathCameraShakeClass) {
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
	}
}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	// When a direction of two vector needs to be calculated, its only needed to subtract the destination location of the start location
	// so destination.location - start.location
	// Do not forget we are workig with WORLD SPACE ROTATION not the local one
	// We need the turret mesh location as we are going to be moving that specific mesh - that is why we dont use GetActorLocation()
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();

	// We can convert the vector location to rotation like this - ToTarget.Rotation()
	// We only want to manipulate the Yaw axis so we dont rotate the turret down for example
	// as it the Rotation function return point on the ground, the turret would be looking
	// down on the ground which we dont want to
	FRotator LookAtRotation = FRotator(0, ToTarget.Rotation().Yaw, 0);

	// As we did calculation using world coordination
	// we need to set the WORLD rotation not the local one
	TurretMesh->SetWorldRotation(
		FMath::RInterpTo( // This is a function to smooth our rotation
			TurretMesh->GetComponentRotation(), // It takes the component rotation
			LookAtRotation, // The calculated rotation our mesh should rotate to
			UGameplayStatics::GetWorldDeltaSeconds(this), // delta time ofcourse to smooth things out
			15.f // and the speed of the rotation
		)
	);
}

void ABasePawn::Fire()
{
	FVector ProjectileSpawnPointLocation = ProjectileSpawnPoint->GetComponentLocation();

	FRotator Rotation = FRotator(0, 0, 0);

	// This function takes care of spawning a class that can be a blueprint rather then a C++ class
	// This way we can spawn actors such as a bullet in our example
	// First we need to provide a type of a class we want to spawn
	// Then the first Parameter is the actuall Object (Actor) with mesh that we want to spawn
	// Second and third argumets are the object location to spawn and rotation respectivaly
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileClass,
		ProjectileSpawnPointLocation,
		ProjectileSpawnPoint->GetComponentRotation()
	);

	// We need to set this BasePawn as the owner of the projectile so
	// in case we call GetOwner from the Projectile class, it will
	// return this BasePawn class
	// see Projectile.cpp - function OnHit - line 36
	Projectile->SetOwner(this);
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
