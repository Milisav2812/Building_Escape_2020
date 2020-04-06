// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldPosition.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Controller.h"

// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();

	auto ActorName = GetOwner()->GetName();
	auto ActorPosition = GetOwner()->GetActorLocation();

	UE_LOG(LogTemp, Warning, TEXT("Actor Name: %s"), *ActorName)
	UE_LOG(LogTemp, Warning, TEXT("Actor Location: [%f, %f, %f]"), ActorPosition.X, ActorPosition.Y, ActorPosition.Z)

	// ...
	
}


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

