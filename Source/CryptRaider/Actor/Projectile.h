// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseInteractible.h"
#include "Projectile.generated.h"

/**
 * 
 */
UCLASS()
class CRYPTRAIDER_API AProjectile : public ABaseInteractible
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
};
