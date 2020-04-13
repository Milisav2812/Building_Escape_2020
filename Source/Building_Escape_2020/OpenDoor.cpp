// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"

#define OUT_PARAM

//#include "GameFramework/DefaultPawn.h"
//#include "GameFramework/Controller.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// Get CurrentYaw and set Target Yaw
	CurrentDoorAngle = GetOwner()->GetActorRotation().Yaw;
	CloseDoorAngle = CurrentDoorAngle;
	OpenDoorAngle = CurrentDoorAngle + OpeningAngle;

	ActorThatTriggersPressurePlate = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// UE_LOG(LogTemp, Warning, TEXT("DoorYaw: %f"), CurrentDoorYaw)
	if (!ensure(PressurePlate)) return;
	
	if (TotalMassOfActorsOnPressurePlate() >= MassThatOpensDoor)
	{
		OpenDoor(DeltaTime);
		DoorLastOpened = GetWorld()->GetTimeSeconds(); // Returns the time in seconds since the Game was started
	}
	else
	{
		if ( (GetWorld()->GetTimeSeconds() - DoorLastOpened) > DoorCloseDelay)
		{
			CloseDoor(DeltaTime);
		}
	}
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	// UE_LOG(LogTemp, Warning, TEXT("DoorOpen: %f"), CurrentDoorYaw)
	CurrentDoorAngle = FMath::FInterpTo(CurrentDoorAngle, OpenDoorAngle, DeltaTime, 2);
	GetOwner()->SetActorRotation(FRotator(0, CurrentDoorAngle, 0));
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	// UE_LOG(LogTemp, Error, TEXT("DoorClose: %f"), CurrentDoorYaw)
	CurrentDoorAngle = FMath::FInterpTo(CurrentDoorAngle, CloseDoorAngle, DeltaTime, 2);
	// ALTERNATIVE CurrentDoorAngle = FMath::Lerp(CurrentDoorAngle, CloseDoorAngle, DeltaTime * .8f);
	GetOwner()->SetActorRotation(FRotator(0, CurrentDoorAngle, 0));
}

float UOpenDoor::TotalMassOfActorsOnPressurePlate() const
{
	TArray<AActor*> ActorsOnPressurePlate;
	PressurePlate->GetOverlappingActors(OUT_PARAM ActorsOnPressurePlate);
	float TotalMass = 0.f;

	for (auto Actor : ActorsOnPressurePlate)
	{
		UPrimitiveComponent* ActorComponent = static_cast<UPrimitiveComponent*>(Actor->GetRootComponent());
		TotalMass += ActorComponent->GetMass();
	}

	return TotalMass;
}

