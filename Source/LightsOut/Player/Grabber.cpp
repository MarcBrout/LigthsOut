// Copyright Marc Brout 2018

#include "Grabber.h"
#include "Components/PrimitiveComponent.h"
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

	PlayerController = GetWorld()->GetFirstPlayerController();
	handle = GetComponentFromOwner<UPhysicsHandleComponent>("physics handle");
	input = GetComponentFromOwner<UInputComponent>("input component");

	if (input) {
		input->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		input->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
}


void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabbing"));
	TSharedPtr<FHitResult> Hit = GetFirstHit();

	if (Hit.IsValid()) {
		AActor * HittedActor = Hit->GetActor();
		if (HittedActor) {
			UE_LOG(LogTemp, Warning, TEXT("Hitting this : %s"), *HittedActor->GetName());
			if (handle) {
				handle->GrabComponentAtLocation(
					Hit->GetComponent(), 
					FName(), 
					Hit->GetComponent()->GetOwner()->GetActorLocation()
				);
			}
		}
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Releasing"));
	if (handle) {
		if (handle->GrabbedComponent)
			handle->ReleaseComponent();
	}
}

TSharedPtr<FHitResult> UGrabber::GetFirstHit()
{
	FRotator PlayerRotation;
	FVector PlayerLocation;

	PlayerController->GetPlayerViewPoint(OUT PlayerLocation, OUT PlayerRotation);

	// Determining the point
	FVector LineTraceEnd = PlayerLocation + PlayerRotation.Vector() * GrabberReach;
	TSharedPtr<FHitResult> Hit(new FHitResult());

	// Setup query params
	FCollisionQueryParams QueryParams(FName(TEXT("")), false, PlayerController);

	// Ray-cast and see if it hits a movable object in reach distance
	GetWorld()->LineTraceSingleByObjectType(
		OUT *Hit.Get(),
		PlayerLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		QueryParams
	);

	return Hit;
}

FVector UGrabber::getLineTraceEnd()
{
	FRotator PlayerRotation;
	FVector PlayerLocation;

	PlayerController->GetPlayerViewPoint(OUT PlayerLocation, OUT PlayerRotation);

	// Determining the point
	return PlayerLocation + PlayerRotation.Vector() * GrabberReach;;
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//DrawDebugLine(GetWorld(), PlayerLocation, LineTraceEnd, FColor::Red, false, -1.f, 0, 5.f);
	if (handle) {
		if (handle->GrabbedComponent) {
			FVector target = getLineTraceEnd();

			handle->SetTargetLocation(target);
		}
	}
}

