// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "BaseHandInteractor.h"

#include "Grabber.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGrabbedUpdate, const class AProjectile*, Projectile);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRYPTRAIDER_API UGrabber : public UBaseHandInteractor
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGrabber();

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	virtual void Interact() override;
	
	UFUNCTION(BlueprintCallable)
	void Grab();

	UFUNCTION(BlueprintCallable)
	void Release();

	UFUNCTION(BlueprintCallable)
	void Throw();

	UFUNCTION(BlueprintCallable)
	virtual FText ConstructHint() const override;

private:
	AProjectile* GetProjectileInReach() const;
	AProjectile* GetGrabbed() const;

	UPhysicsHandleComponent* GetPhysicsHandle() const;

public:
	FGrabbedUpdate OnGrabbedUpdated;
	
private:
	UPROPERTY(EditAnywhere)
	float HoldDistance = 200;

	UPROPERTY(EditAnywhere)
	float ThrowImpulseStrength = 1500;

	FName GrabbedTag = "Grabbed";
};
