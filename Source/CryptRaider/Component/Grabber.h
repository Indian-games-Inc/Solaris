// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRYPTRAIDER_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGrabber();

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Interact();
	
	UFUNCTION(BlueprintCallable)
	void Grab();

	UFUNCTION(BlueprintCallable)
	void Release();

	UFUNCTION(BlueprintCallable)
	void Throw();

	UFUNCTION(BlueprintCallable)
	bool IsGrabbing() const;  // TODO Remove this shit
	FString GetGrabbedItemName() const;  // TODO Remove this shit too

	UFUNCTION(BlueprintCallable)
	FText ConstructHintMessage() const;

private:

	
	class AProjectile* GetProjectileInReach() const;
	AProjectile* GetGrabbed() const;

	UPhysicsHandleComponent* GetPhysicsHandle() const;
	class UHand* GetHand() const;
	class ABasePlayerController* GetController() const;

private:
	UPROPERTY(EditAnywhere)
	float HoldDistance = 200;

	UPROPERTY(EditAnywhere)
	float ThrowImpulseStrength = 1500;

	FName GrabbedTag = "Grabbed";
};
