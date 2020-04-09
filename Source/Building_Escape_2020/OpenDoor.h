// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"

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

private:
	float CurrentDoorYaw;
	float OpenDoorYaw;

	UPROPERTY(EditAnywhere)
	float Increment = 90; // By how much we want the door to open

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;

	// UPROPERTY(EditAnywhere)
	AActor* ActorThatTriggersPressurePlate = nullptr;
		
};
