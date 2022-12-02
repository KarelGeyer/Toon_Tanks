// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealtComponent.generated.h"


/// <summary>
	/// This class inherits from UActorComponent component which is a lot different then Actor class.
	/// It is only a component that has no visual attachments for instance, so it is only used for running some code
	/// It is also BlueprintSpawnableComponent which allows us to add this component in Blueprints
	/// </summary>
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UHealtComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHealtComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
		float MaxHealth = 100.f;

	float Health = 0.f;

	class AToonTanksGameMode* ToonTanksGameMode;

	/// <summary>
	/// This function takes care of the  Applying the damage and reducing Healt.
	/// First Param is the Damaged Actor object.
	/// Second Param represents the total Damage caused to the Actor object.
	/// Third Param represents a type of damage (e.g. poison damage, fire damage) based on which we can apply different functionality.
	/// Fourth Param Instigator is controller responsible for the damage -> needs to be forward declared.
	/// Fifth represents and Actor that actually caused the damage, so in our case it is the Projectile itself.
	/// This function is triggered in <see cref="AProjectile::OnHit"/>
	/// </summary>
	UFUNCTION()
		void DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* Instigator, AActor* DamageCauser);

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};
