// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "Components/AudioComponent.h"
#include "OpenDoor_SpecificActor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_2020_API UOpenDoor_SpecificActor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor_SpecificActor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);

private:

	float CurrentAngle;
	float OpenAngle;
	float CloseAngle;

	bool bIsDoorOpening = false;
	bool bIsDoorClosing = true;

	UPROPERTY(EditAnywhere)
	float AngleIncrement = 90.f; // By how many degrees to open the door

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
	AActor* ActorThatOpensDoor = nullptr;

	UPROPERTY(EditAnywhere)
	UAudioComponent* AudioComponent = nullptr;

	// Helper Functions
	void InitAudioComponent();
};
