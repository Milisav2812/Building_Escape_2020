// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor_SpecificActor.h"

// Sets default values for this component's properties
UOpenDoor_SpecificActor::UOpenDoor_SpecificActor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor_SpecificActor::BeginPlay()
{
	Super::BeginPlay();

	CurrentAngle = GetOwner()->GetActorRotation().Yaw;
	OpenAngle = CurrentAngle + AngleIncrement;
	CloseAngle = CurrentAngle;

	InitAudioComponent();

	if (!ensure(PressurePlate) || !ensure(ActorThatOpensDoor)) return;
}


// Called every frame
void UOpenDoor_SpecificActor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate && ActorThatOpensDoor)
	{
		if (PressurePlate->IsOverlappingActor(ActorThatOpensDoor))
		{
			OpenDoor(DeltaTime);
		}
		else
		{
			CloseDoor(DeltaTime);
		}
	}
}

void UOpenDoor_SpecificActor::OpenDoor(float DeltaTime)
{
	CurrentAngle = FMath::Lerp(CurrentAngle, OpenAngle, DeltaTime * 0.8f);
	FRotator DoorRotation = FRotator(0, CurrentAngle, 0);
	GetOwner()->SetActorRotation(DoorRotation);

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

void UOpenDoor_SpecificActor::CloseDoor(float DeltaTime)
{
	CurrentAngle = FMath::Lerp(CurrentAngle, CloseAngle, DeltaTime * 0.8f);
	FRotator DoorRotation = FRotator(0, CurrentAngle, 0);
	GetOwner()->SetActorRotation(DoorRotation);

	if (ensure(AudioComponent))
	{
		if (FMath::IsNearlyEqual(CurrentAngle, CloseAngle, 3.f))
		{
			bIsDoorOpening = false;
			if (!bIsDoorClosing)
			{
				AudioComponent->Play();
				bIsDoorClosing = true;
			}
		}
	}
}

void UOpenDoor_SpecificActor::InitAudioComponent()
{
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
	if (!ensure(AudioComponent)) return;
}

