#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include <Kismet/GameplayStatics.h>
#include <Particles/ParticleSystemComponent.h>


AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = false; // We do not need to tick function

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovementComponent->MaxSpeed = 1000.f;
	ProjectileMovementComponent->InitialSpeed = 1000.f;

	TrailParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle System Component"));
	TrailParticles->SetupAttachment(RootComponent);
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	/// <summary>
	/// This few lines takes care of actually binding our OnHit Function with our mesh
	/// Basically Whenever our ProjectileMesh Hits something, This add the function to a list of function that needs to called
	/// and then the function is called
	/// First Parameter represents the class that is hitting something, so THIS
	/// Second Parameter repesents a callback function that will be added to the invokation list and called.
	/// Once it triggers a function <see cref=AProjectile::OnHit></see> is called.
	/// This Adddynamic is basically an ekvivalent to en event in C# Unity when the engine waits for
	/// a certain event to happen and when it does, it triggers this function.
	/// Basicaly it goes as follows:
	/// 1. Component is hit
	/// 2. OnHit function is triggered
	/// 3. OnHit calls ApplyDamage
	/// 4. In Health Component, OnDamageTaken evene is registered
	/// 5. Function <see cref=UHealtComponent::DamageTaken></see> is called
	/// </summary>
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	if (LaunchSound) {
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
	}

}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/// <summary>
/// This Function takes care fo caling engine in-built function Applydamage which checkes for a damage event to trigger
/// and when it does, it executes the code within it. We also take care of destroying the projectile when it hits something
/// The event it self is on line 29 and it triggeres a function on HealComponent class
/// <see cref=UHealtComponent::DamageTaken></see>.
/// </summary>
void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* MyOwner = GetOwner();
	if (MyOwner == nullptr) return;


	AController* MyOwnerInstigator = MyOwner->GetInstigatorController();
	UClass* DamageTypeClass = UDamageType::StaticClass();

	if (OtherActor && OtherActor != this && OtherActor != MyOwner) {
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, this, DamageTypeClass);


		if (HitSound) {
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
		}

		/// <summary>
		///  This way we can spawn and show particle effects -> we are showing cloud effect
		/// </summary>
		if (HitParticles) {
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation());
		}

		if (HitCameraShakeClass) {
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
		}

		Destroy();
	}


}

