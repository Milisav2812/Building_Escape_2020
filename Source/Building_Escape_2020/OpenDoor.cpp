// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

//#include "GameFramework/DefaultPawn.h"
//#include "GameFramework/Controller.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// Get CurrentYaw and set Target Yaw
	CurrentDoorYaw = GetOwner()->GetActorRotation().Yaw;
	CloseDoorYaw = CurrentDoorYaw;
	OpenDoorYaw = CurrentDoorYaw + Increment;

	ActorThatTriggersPressurePlate = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// UE_LOG(LogTemp, Warning, TEXT("DoorYaw: %f"), CurrentDoorYaw)
	if (!ensure(PressurePlate)) return;
	
	if (PressurePlate->IsOverlappingActor(ActorThatTriggersPressurePlate))
	{
		OpenDoor(DeltaTime);
	}
	else
	{
		CloseDoor(DeltaTime);
	}
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	// UE_LOG(LogTemp, Warning, TEXT("DoorOpen: %f"), CurrentDoorYaw)
	CurrentDoorYaw = FMath::FInterpTo(CurrentDoorYaw, OpenDoorYaw, DeltaTime, 2);
	GetOwner()->SetActorRotation(FRotator(0, CurrentDoorYaw, 0));
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	// UE_LOG(LogTemp, Error, TEXT("DoorClose: %f"), CurrentDoorYaw)
	CurrentDoorYaw = FMath::FInterpTo(CurrentDoorYaw, CloseDoorYaw, DeltaTime, 2);
	GetOwner()->SetActorRotation(FRotator(0, CurrentDoorYaw, 0));
}

