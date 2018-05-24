// Copyright Marc Brout 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "DoorOpener.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LIGHTSOUT_API UDoorOpener : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorOpener();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void openDoor(float angle);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	AActor * owner;
	
	UPROPERTY(EditAnywhere)
	float OpenAngle;

	UPROPERTY(EditAnywhere)
	ATriggerVolume *trigger;

	UPROPERTY(EditAnywhere)
 	TArray<AActor *> openers;
};
