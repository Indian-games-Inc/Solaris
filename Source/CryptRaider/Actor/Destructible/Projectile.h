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

	virtual bool IsCharged() const;
	virtual void Charge();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void AddForce(const FVector& Location) const;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AFieldSystemActor> MasterFieldClass;

	UPROPERTY(EditDefaultsOnly)
	float MasterFieldDestructionDelay = 5.0f;

	FName GrabbedTag = "Grabbed";

	UPROPERTY()
	bool bIsCharged = false;
};
