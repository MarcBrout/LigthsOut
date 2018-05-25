// Copyright Marc Brout 2018

#include "DoorOpener.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

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


void UDoorOpener::openDoor(float angle)
{
	FRotator rot = FRotator(0.f, angle, 0.f);
	owner->SetActorRotation(rot);
}


// Called every frame
void UDoorOpener::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	bool bIsTriggerOverlaped = false;

//	 If the one autorised opener for the openers array overlap the trigger, open the door
	for (TWeakObjectPtr<AActor>& actor : openers) {
		if (actor.IsValid() && trigger->IsOverlappingActor(actor.Get())) {
			openDoor(-40.f);
			bIsTriggerOverlaped = true;
		}
	}

	if (!bIsTriggerOverlaped) {
		openDoor(0.f);
	}
}

