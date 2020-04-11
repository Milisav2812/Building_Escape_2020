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

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!ensure(PhysicsHandle)) return;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

#pragma region Get Player ViewPoint

	FVector PlayerViewLocation;
	FRotator PlayerViewRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT_PARAM PlayerViewLocation, 
		OUT_PARAM PlayerViewRotation
	);

	//UE_LOG(LogTemp, Warning, TEXT("PlayerViewLocation: %s"), *PlayerViewLocation.ToString())
	//UE_LOG(LogTemp, Warning, TEXT("PlayerViewRotation: %s"), *PlayerViewRotation.ToString())
#pragma endregion
	
#pragma region Draw Debug Line

	FVector LineTraceStart = PlayerViewLocation;
	FVector LineTraceEnd = LineTraceStart + PlayerViewRotation.Vector() * GrabberReach;

	DrawDebugLine(
		GetWorld(), 
		LineTraceStart,
		LineTraceEnd,
		FColor::Green,
		NULL,
		NULL,
		NULL,
		5
	);
#pragma endregion

#pragma region Ray-Casting
	FHitResult Hit{};
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

	if (Hit.GetActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("HitResult: %s"), *Hit.GetActor()->GetName())
	}
	
#pragma endregion

}

