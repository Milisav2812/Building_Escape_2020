// Fill out your copyright notice in the Description page of Project Settings.


#include "RaiseDoorA.h"

// Sets default values for this component's properties
URaiseDoorA::URaiseDoorA()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URaiseDoorA::BeginPlay()
{
	Super::BeginPlay();

	DoorLocation = GetOwner()->GetActorLocation();
	OpenZ = DoorLocation.Z + OpenIncrement;
	CloseZ = DoorLocation.Z;

	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
}


// Called every frame
void URaiseDoorA::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!ensure(PressurePlate)) return;

	if (PressurePlate->IsOverlappingActor(OpenActor1) || PressurePlate->IsOverlappingActor(OpenActor2))
	{
		OpenDoor(DeltaTime);
	}
	else
	{
		CloseDoor(DeltaTime);
	}
}


void URaiseDoorA::OpenDoor(float DeltaTime)
{
	DoorLocation.Z = FMath::Lerp(DoorLocation.Z, OpenZ, DeltaTime * 0.4f);
	GetOwner()->SetActorLocation(DoorLocation);

	if (ensure(AudioComponent))
	{
		bIsDoorClosing = false;
		if (!bIsDoorOpening)
		{
			AudioComponent->Play();
			bIsDoorOpening = true;
		}
	}

}

void URaiseDoorA::CloseDoor(float DeltaTime)
{
	DoorLocation.Z = FMath::Lerp(DoorLocation.Z, CloseZ, DeltaTime * 0.4f);
	GetOwner()->SetActorLocation(DoorLocation);

	if (ensure(AudioComponent))
	{
		bIsDoorOpening = false;
		if (!bIsDoorClosing)
		{
			AudioComponent->Play();
			bIsDoorClosing = true;
		}
	}
}
