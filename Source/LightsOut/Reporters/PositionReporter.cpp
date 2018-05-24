// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/Actor.h"
#include "PositionReporter.h"

// Sets default values for this component's properties
UPositionReporter::UPositionReporter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPositionReporter::BeginPlay()
{
	Super::BeginPlay();
	owner = GetOwner();

	FString name = owner->GetName();

	UE_LOG(LogTemp, Warning, TEXT("Position reporter: reporting for %s!"), *name);
	
}


// Called every frame
void UPositionReporter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	// UE_LOG(LogTemp, Warning, TEXT("Position reporter: reporting for duty!"));
}

