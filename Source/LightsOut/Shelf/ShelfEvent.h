// Copyright Marc Brout 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "ShelfEvent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTrigger);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LIGHTSOUT_API UShelfEvent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UShelfEvent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
	ATriggerVolume *TriggerPlate = nullptr;

	UPROPERTY(EditAnywhere)
	AActor *Trigger = nullptr;

	UPROPERTY(BlueprintAssignable)
	FOnTrigger OnTrigger;
};
