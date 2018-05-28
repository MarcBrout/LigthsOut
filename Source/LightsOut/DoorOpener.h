// Copyright Marc Brout 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "DoorOpener.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOpening, float, angle);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnClosing);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LIGHTSOUT_API UDoorOpener : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorOpener();
	float GetOpenAngleTick() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	float GetTotalMassOfActorsOnPlate() const;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	AActor * owner;
	float LastDoorOpenTime = 0.f;
	
	UPROPERTY(EditAnywhere)
	float OpenAngleTick;

	UPROPERTY(EditAnywhere)
	ATriggerVolume *trigger;

	UPROPERTY(EditAnywhere)
 	TArray<AActor*> openers;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 1.f;

	UPROPERTY(EditAnywhere)
	float MassRequiredToTriggerOpenTick = 30.f;

	UPROPERTY(BlueprintAssignable)
	FOnOpening OnOpening;

	UPROPERTY(BlueprintAssignable)
	FOnClosing OnClosing;
};
