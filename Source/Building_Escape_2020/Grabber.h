// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_2020_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void Grab();
	void Release();
	// Return the first Actor within range that has a PhysicsBody Collion Channel set
	FHitResult GetFirstPhysicsBodyInReach();

private:
	UPROPERTY(EditDefaultsOnly)
	float GrabberReach = 120.f;

	// Players Position in The World
	FVector RayCastStart;
	// Location of the The End of Ray-Cast
	FVector RayCastEnd;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;

	// Helper Functions
	void InitPhysicsHandle();
	void InitInputComponent();
	// Calculate the Start and End Locations of Ray-Cast(FVectors)
	void CalculateRayCastLocation(FVector& OUT_RayCastStart, FVector& OUT_RayCastEnd);
};
