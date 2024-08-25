// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGrabberHintUpdate, const FText&, Hints);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRYPTRAIDER_API UGrabber : public USceneComponent
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
	void Grab(const FHitResult& HitResult);

	UFUNCTION(BlueprintCallable)
	void Release();

	UFUNCTION(BlueprintCallable)
	void Throw();

	UFUNCTION(BlueprintCallable)
	bool IsGrabbing() const;
	FString GetGrabbedItemName() const;

private:
	FText ConstructHintMessage() const;
	
	UPrimitiveComponent* GetGrabbed() const;
	UPhysicsHandleComponent* GetPhysicsHandle() const;

	class UHand* GetHand() const;
	class ABasePlayerController* GetController() const;
	
public:
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FGrabberHintUpdate OnHintUpdated;
	
private:
	UPROPERTY(EditAnywhere)
	float MaxGrabDistance = 200;

	UPROPERTY(EditAnywhere)
	float GrabRadius = 20;

	UPROPERTY(EditAnywhere)
	float HoldDistance = 200;

	UPROPERTY(EditAnywhere)
	float ThrowImpulseStrength = 1500;

	FName GrabbedTag = "Grabbed";
};
