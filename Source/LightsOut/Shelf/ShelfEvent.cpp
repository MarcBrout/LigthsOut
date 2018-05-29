// Copyright Marc Brout 2018

#include "ShelfEvent.h"


// Sets default values for this component's properties
UShelfEvent::UShelfEvent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UShelfEvent::BeginPlay()
{
	Super::BeginPlay();

	if (TriggerPlate == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Trigger Plate missing from %s !"), *GetOwner()->GetName());
	}
	if (Trigger == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Triggerer missing from %s !"), *GetOwner()->GetName());
	}
}


// Called every frame
void UShelfEvent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Trigger && TriggerPlate) {
		if (TriggerPlate->IsOverlappingActor(Trigger)) {
			UE_LOG(LogTemp, Error, TEXT("TriggerING !"));

			OnTrigger.Broadcast();
		}
	}
}

