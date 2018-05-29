// Copyright Marc Brout 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "SharedPointer.h"
#include "Engine/SpotLight.h"
#include "Grabber.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCubeGrab);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCubeRelease);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LIGHTSOUT_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	template<typename T>
	T* GetComponentFromOwner(FString const &name) {
		T* comp = nullptr;
		comp = GetOwner()->FindComponentByClass<T>();
		if (comp == nullptr) {
			UE_LOG(LogTemp, Error, TEXT("There is no '%s' on : %s"), *name, *PlayerController->GetName())
		}
		return comp;
	}

	void Grab();
	void Release();
	TSharedPtr<FHitResult> GetFirstHit();
	FVector getLineTraceEnd();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	APlayerController* PlayerController = nullptr;

	UPROPERTY(EditAnywhere)
	float GrabberReach = 100.f;
	
	UPhysicsHandleComponent* handle = nullptr;
	UInputComponent* input = nullptr;

	UPROPERTY(BlueprintAssignable)
	FOnCubeGrab OnCubeGrab;

	UPROPERTY(BlueprintAssignable)
	FOnCubeRelease OnCubeRelease;
};
