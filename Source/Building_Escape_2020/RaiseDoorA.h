// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "Components/AudioComponent.h"
#include "RaiseDoorA.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_2020_API URaiseDoorA : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URaiseDoorA();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);

private:
	FVector DoorLocation;

	float CurrentZ;
	float OpenZ = 300.f;
	float CloseZ = 410.f;

	bool bIsDoorOpening = true;
	bool bIsDoorClosing = false;

	UPROPERTY(EditAnywhere)
		float OpenIncrement = 300.f; // By how many degrees to open the door

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
	AActor* OpenActor1 = nullptr;

	UPROPERTY(EditAnywhere)
	AActor* OpenActor2 = nullptr;

	
	UAudioComponent* AudioComponent = nullptr;
		
};
