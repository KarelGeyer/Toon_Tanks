// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <Kismet/GameplayStatics.h>
#include <DrawDebugHelpers.h>

ATank::ATank() {
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// We can create camera components like this
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Tank Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Tank Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	// CASTING
	// Casting is used when we need to access a child of a class of the same Type
	// Getcontroller return a AController which is not what we want
	// We want a APlayerController which is a subclass of AController in the hierarchy -> see documentation of AController
	// We can use Casting with Cast<>() function to convert AController to APLayerController
	// This is used to get a reference to our controller EG. MOUSE location
	TankPlayerController = Cast<APlayerController>(GetController());
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	// Line Trace - casting a line from point a to point b a detecting a collision (if there is any) between these points
	// Kinda like RAY CAST in unity
	// FHitResult contains information about the object we hit
	if (TankPlayerController) {
		// We want to get our mouse cursor point in the world so we can do:
		// 1. rotate our top part of the tank
		// 2. aim and shoot
		FHitResult HitResult;
		TankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);

		////**** This will draw a debug sphere on our cursor location ****////
		//DrawDebugSphere(
		//	GetWorld(), // Get world
		//	HitResult.ImpactPoint, // Location of the center of the sphere
		//	25.f, // size
		//	12, // segments defines how round the spehere will be
		//	FColor::Red,
		//	false, // persistence of the sphere
		//	-1.f // how long it is in the world - -1 means only for one frame
		//);

		// Here we call a function from the Parent class BasePawn to rotate
		// the top part of our tank
		RotateTurret(HitResult.ImpactPoint);
	}
}

/// <summary>
/// This function serves as an inherited contstructor of sort
/// The first implementation is in the BasePawn::HandleDestruction
/// This is calling the Super method to execute the code in BasePawn::HandleDestruction
/// and on top of that it is going to execute some its own code to destroy the pawn.
/// Please check Function AToonTanksGameMode::ActorDied for more info.
/// </summary>
void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	isTankAlive = false;
	// Destroy(); // this is causing game to crash;
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// This will call the instructor of the Parent function (In our case it is the parent of the BasePawn as
	// basepawn does not impelement this function
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Make sure you are binding the proper input type name -> MoveForward or Turn
	// As BindAxis works with Axis mappings, it runs every tick automatically
	// BindAxis takes a name of the specific mapping, object to bind to and a callback function to run every tick
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);

	// Bind Action works similarly like Bind Axis
	// The difference is that it runs based on event like click or button released rather then every tick
	// It also accepts additional parameters such as IE_Pressed or IE_Released which function is rather self-explanatory
	PlayerInputComponent->BindAction(TEXT("Fire"),IE_Pressed, this, &ATank::Fire);
}

// In the input setting in the editor, there are values set to both keys W and S
	// W = 1.0
	// S = -1.0
	// The value of this function's Values is exactly that, when we press w, the value is going to be 1 and -1 when we press s
void ATank::Move(float Value)
{
	// We can declare a Vector that is going to be zero and set it's X value to the argument Value * DeltaTime * Speed
	// Then it is going to take take value 1 or - 1 depending on whether we are clicking on W or S and scale it based on Delta time and speed
	// And that is it, our character is moving on its X axis
	// Do not forget this function is called from line 31, not from Tick function
	FVector DeltaLocation = FVector::ZeroVector;
	DeltaLocation.X = Value * UGameplayStatics::GetWorldDeltaSeconds(this) * Speed;
	// This function is an inbuilt fundtion manipulation our character's axis and we allow sweep for collisions
	AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float Value)
{
	// This generaly does the same thing as ATank::Move(float Value) but for the rotation rather then movement
	// We want to rotate around the YAW Axis, Click on FRotator docs to see what it means
	FRotator DeltaRotation = FRotator::ZeroRotator;
	DeltaRotation.Yaw = Value * UGameplayStatics::GetWorldDeltaSeconds(this) * TurnRate;
	AddActorLocalRotation(DeltaRotation, true);
}
