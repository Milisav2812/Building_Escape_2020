// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelComplete.h"

// Sets default values for this component's properties
ULevelComplete::ULevelComplete()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULevelComplete::BeginPlay()
{
	Super::BeginPlay();

	DoorLocation = GetOwner()->GetActorLocation();
	OpenZ = DoorLocation.Z + OpenIncrement;

	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
	
}


// Called every frame
void ULevelComplete::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!ensure(PressurePlate)) return;

	if (PressurePlate->IsOverlappingActor(OpenActor))
	{
		OpenDoor(DeltaTime);
	}
}

void ULevelComplete::OpenDoor(float DeltaTime)
{
	DoorLocation.Z = FMath::Lerp(DoorLocation.Z, OpenZ, DeltaTime * 1.5f);
	GetOwner()->SetActorLocation(DoorLocation);

	if (ensure(AudioComponent))
	{
		if (!bIsDoorOpening)
		{
			AudioComponent->Play();
			bIsDoorOpening = true;
		}
	}

}
