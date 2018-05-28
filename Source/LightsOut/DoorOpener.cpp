// Copyright Marc Brout 2018

#include "DoorOpener.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"

#define OUT

// Sets default values for this component's properties
UDoorOpener::UDoorOpener()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorOpener::BeginPlay()
{
	Super::BeginPlay();

	owner = GetOwner();

	// Adding the main player to the list of openers
	AActor* actor = GetWorld()->GetFirstPlayerController()->GetPawn();
	openers.Emplace(actor);
}


void UDoorOpener::RotateDoor(float angle)
{
	owner->SetActorRotation(FRotator(0.f, angle, 0.f));
}

float UDoorOpener::GetTotalMassOfActorsOnPlate() const
{
	float TotalMass = 0.f;
	TArray<AActor*> OverlappingActors;

	trigger->GetOverlappingActors(OUT OverlappingActors);
	for (AActor* actor : OverlappingActors) {
		if (openers.Find(actor) != INDEX_NONE)
			TotalMass += actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	UE_LOG(LogTemp, Warning, TEXT("TotalMass  = %f"), TotalMass);
	return TotalMass;
}


// Called every frame
void UDoorOpener::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
//	 If the one autorised opener for the openers array overlap the trigger, open the door
	float totalMass = GetTotalMassOfActorsOnPlate();
	if (totalMass > 0) {
		int times = totalMass / MassRequiredToTriggerOpenTick;

		RotateDoor(OpenAngleTick * times);
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	// close the door after some times
	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay) {
		RotateDoor(0.f);
	}
}

