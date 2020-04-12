#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

#define OUT_PARAM // Used to mark OUT parameters in function calls

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	InitPhysicsHandle();
	InitInputComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Object Grabbed!"))
	AActor* ActorGrabbed = GetFirstPhysicsBodyInReach();
	if (ActorGrabbed)
	{
		UE_LOG(LogTemp, Warning, TEXT("ActorHit: %s"), *ActorGrabbed->GetName())
	}
}
void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Object Released!"))
}

// Return the first Actor within range that has a PhysicsBody Collion Channel set
AActor* UGrabber::GetFirstPhysicsBodyInReach() const
{
#pragma region Get Player ViewPoint
	
	FVector PlayerViewLocation;
	FRotator PlayerViewRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT_PARAM PlayerViewLocation,
		OUT_PARAM PlayerViewRotation
	);
#pragma endregion

#pragma region Draw Debug Line

	FVector LineTraceStart = PlayerViewLocation;
	FVector LineTraceEnd = LineTraceStart + PlayerViewRotation.Vector() * GrabberReach;

	//DrawDebugLine(
	//	GetWorld(),
	//	LineTraceStart,
	//	LineTraceEnd,
	//	FColor::Green,
	//	NULL,
	//	NULL,
	//	NULL,
	//	5
	//);
#pragma endregion

#pragma region Ray-Casting
	
	FHitResult Hit;

	FCollisionQueryParams TraceParams(
		FName(TEXT("")),
		false, // Use Complex or Simple Collision
		GetOwner() // The Actor that the Ray-Cast will ignore
	);

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		LineTraceStart,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), // Our Ray-Cast will only respond to PhysicsBody objects
		TraceParams
	);
#pragma endregion

	AActor* ActorHitWithRayCast = Hit.GetActor();
	if (Hit.GetActor())
	{
		return ActorHitWithRayCast;
	}
	return nullptr;
}

void UGrabber::InitPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("PhysicsHandle Returns NULL!"))
			return;
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("PhysicsHandle WORKS!"))
	}
}
void UGrabber::InitInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (!InputComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("InputComponent Returns NULL!"))
			return;
	}
	else
	{
		// UE_LOG(LogTemp, Warning, TEXT("InputComponent WORKS!"))
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
}

