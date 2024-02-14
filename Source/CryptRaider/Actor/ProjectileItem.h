// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "ProjectileItem.generated.h"

/**
 * 
 */
UCLASS()
class CRYPTRAIDER_API AProjectileItem : public AItem
{
	GENERATED_BODY()

public:
	virtual void OnComponentHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
								UPrimitiveComponent* OtherComp, FVector NormalImpulse,
								const FHitResult& Hit) override;

private:
	UFUNCTION()
	void AddForce(const FVector& Location) const;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AFieldSystemActor> MasterFieldClass;

	UPROPERTY(EditDefaultsOnly)
	float MasterFieldDestructionDelay = 5.0f;
};
