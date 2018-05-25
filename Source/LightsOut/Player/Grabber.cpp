// Copyright Marc Brout 2018

#include "Engine/World.h"
#include "Grabber.h"
#include "DrawDebugHelpers.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber created for : %s"), *GetOwner()->GetName())
	PlayerController = GetWorld()->GetFirstPlayerController();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get Player View Point
	FRotator PlayerRotation;
	FVector PlayerLocation;

	PlayerController->GetPlayerViewPoint(OUT PlayerLocation, OUT PlayerRotation);

	// Ray-cast and see if it hits a movable object in reach distance
	FVector LineTraceEnd = PlayerLocation + PlayerRotation.Vector() * GrabberRange;

	DrawDebugLine(GetWorld(), PlayerLocation, LineTraceEnd, FColor::Red, false, -1.f, 0, 5.f);
}

