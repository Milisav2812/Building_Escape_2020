// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "Components/AudioComponent.h"

#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_2020_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);

	float TotalMassOfActorsOnPressurePlate() const;

	// Helper Functions
	void InitAudioComponent();

private:
	float CurrentDoorAngle;
	float OpenDoorAngle;
	float CloseDoorAngle;

	// Used for sound
	bool bIsDoorClosing = true;
	bool bIsDoorOpening = false;

	float DoorLastOpened = 0.f;
	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 0.5f;

	UPROPERTY(EditAnywhere)
	float OpeningAngle = 90; // By how much we want the door to open

	UPROPERTY(EditAnywhere)
	float MassThatOpensDoor = 60.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;

	UAudioComponent* AudioComponent = nullptr;
};
