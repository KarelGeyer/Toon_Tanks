// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
		UStaticMeshComponent* ProjectileMesh;

	/// <summary>
	/// ProjectileMovementComponent is a way for us to handle projectiles like bullets for example.
	/// It is an inbuilt way in Unreal Engine where we only add this component, setup few values (max speed, initial speed etc..).
	/// and the engine will take care of the rest for us with its physics.
	/// </summary>
	UPROPERTY(VisibleAnywhere, Category = "Movement")
		class UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditAnywhere)
		float Damage = 50.f;

	/// <summary>
	/// This way we can add particles and effect to our projectile
	/// </summary>
	UPROPERTY(EditAnywhere, Category = "Combat")
		UParticleSystem* HitParticles;

	UPROPERTY(VisibleAnywhere, Category = "Combat")
		UParticleSystemComponent* TrailParticles;

	UPROPERTY(EditAnywhere, Category = "Combat")
		USoundBase* LaunchSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
		USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
		TSubclassOf<class UCameraShakeBase> HitCameraShakeClass;

	/// <summary>
	/// This function takes care of the hitting functionality
	/// It takes several params.
	/// First Parameter (HitComp) is the object that is hitting some other object -> that is our projectile.
	/// Second Parameter (OtherActor) represents the actor that was hit.
	/// Third Parameter (OtherComp) represents a component of OtherActor that got hit.
	/// Fourth Parameter (NormalImpulse) for physics simulation where physics engine applies and impulse in response to the collision.
	/// And the last Param represent the actual HIT result that contains information about the object that was hit.
	/// </summary>
	UFUNCTION()
	void OnHit(
		UPrimitiveComponent* HitComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& Hit
	);

};
