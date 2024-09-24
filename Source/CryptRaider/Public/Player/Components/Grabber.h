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

	float GetInterpSpeed(const float& Mass) const;
	float GetThrowVelocity(const float& Mass) const;

public:
	FGrabbedUpdate OnGrabbedUpdated;
	
private:
	UPROPERTY(EditAnywhere, Category = "Grab",  meta = (AllowPrivateAccess = "true"))
	float HoldDistance = 200.f;

	UPROPERTY(EditAnywhere, Category = "Grab",  meta = (AllowPrivateAccess = "true"))
	float ReleaseDistance = 150.f;

	FName GrabbedTag = "Grabbed";

	
	// Interpolation params
	
	// Used to calculate grab move interpolation speed: greater -> faster
	UPROPERTY(EditAnywhere, Category = "Interpolation", meta = (AllowPrivateAccess = "true"))
	float InterpSpeedConstant = 5000.f;

	UPROPERTY(EditAnywhere, Category = "Interpolation", meta = (AllowPrivateAccess = "true"))
	float MinInterpSpeed = 1.f;
	
	UPROPERTY(EditAnywhere, Category = "Interpolation", meta = (AllowPrivateAccess = "true"))
	float MaxInterpSpeed = 100.f;

	// Throw params
	
	UPROPERTY(EditAnywhere, Category = "Throw", meta = (AllowPrivateAccess = "true"))
	float MaxThrowVelocity = 1000.f;

	UPROPERTY(EditAnywhere, Category = "Throw", meta = (AllowPrivateAccess = "true"))
	float MinThrowVelocity = 200.f;
	
	UPROPERTY(EditAnywhere, Category = "Throw", meta = (AllowPrivateAccess = "true"))
	float MaxObjectMass = 1500.f;
};
