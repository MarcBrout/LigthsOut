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


float UDoorOpener::GetOpenAngleTick() const
{
	return OpenAngleTick;
}

// Called when the game starts
void UDoorOpener::BeginPlay()
{
	Super::BeginPlay();

	owner = GetOwner();

	// Adding the main player to the list of openers
	AActor* actor = GetWorld()->GetFirstPlayerController()->GetPawn();
	openers.Emplace(actor);

	if (trigger == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Trigger missging from %s !"), *GetOwner()->GetName());
	}

	if (openers.Num() == 0) {
		UE_LOG(LogTemp, Error, TEXT("There is no opener added !"));
	}
} 

float UDoorOpener::GetTotalMassOfActorsOnPlate() const
{
	float TotalMass = 0.f;
	TArray<AActor*> OverlappingActors;

	if (trigger) {
		trigger->GetOverlappingActors(OUT OverlappingActors);
		for (AActor* actor : OverlappingActors) {
			if (openers.Find(actor) != INDEX_NONE)
				TotalMass += actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		}
	}

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

		OnOpening.Broadcast(OpenAngleTick * times);
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	// close the door after some times
	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay) {
		OnClosing.Broadcast();
	}
}

