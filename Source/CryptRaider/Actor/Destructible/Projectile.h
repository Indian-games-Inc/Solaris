// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Interface/BaseInteractable.h"
#include "Projectile.generated.h"

/**
 * 
 */
UCLASS()
class CRYPTRAIDER_API AProjectile : public ABaseInteractable
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void OnComponentHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
	                            UPrimitiveComponent* OtherComp, FVector NormalImpulse,
	                            const FHitResult& Hit);

public:
	virtual void Interact() override;
	virtual FString HintMessage() const override;

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void AddForce(const FVector& Location) const;

	UFUNCTION()
	float GetImpulse(const FHitResult& HitResult) const;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AFieldSystemActor> MasterFieldClass;

	UPROPERTY(EditDefaultsOnly)
	float MasterFieldDestructionDelay = 5.0f;

	UPROPERTY(EditDefaultsOnly)
	float HitForceThreshold = 1000.f;

	UPROPERTY(EditDefaultsOnly)
	float StunDuration = 2.f;
	
	FName GrabbedTag = "Grabbed";

	UPROPERTY()
	FVector CurrentVelocity;
};
