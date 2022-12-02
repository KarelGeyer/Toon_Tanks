// Fill out your copyright notice in the Description page of Project Settings.


#include "HealtComponent.h"
#include <Kismet/GameplayStatics.h>
#include "ToonTanksGameMode.h"

UHealtComponent::UHealtComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UHealtComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	/// <summary>
	/// This few lines of code takes care of bidning our Damagetake function to an event
	/// which is taken any damage event.
	/// THis will be paired up with an event called ApplyDamage which is called from parent classes.
	/// This Adddynamic is basically an ekvivalent to en event in C# Unity when the engine waits for
	/// a certain event to happen and when it does, it triggers this function
	/// <see cref=AProjectile::OnHit></see>
	/// </summary>
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealtComponent::DamageTaken);

	ToonTanksGameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));
}


void UHealtComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser)
{
	if (Damage <= 0.f) return;

	Health -= Damage;

	if (Health <= 0.f && ToonTanksGameMode) {
		ToonTanksGameMode->ActorDied(DamagedActor);
	}
}

void UHealtComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

