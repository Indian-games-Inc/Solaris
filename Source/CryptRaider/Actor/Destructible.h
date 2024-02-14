// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GeometryCollection/GeometryCollectionActor.h"
#include "Destructible.generated.h"

UCLASS()
class CRYPTRAIDER_API ADestructible : public AGeometryCollectionActor
{
	GENERATED_BODY()

public:
	virtual void OnDestroy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void DelayedDisableCollision();
	
	void DelayedDestroy();

private:
	UPROPERTY(EditAnywhere)
	float CollisionDisableDelay = 2.0f;

	UPROPERTY(EditAnywhere)
	float DestroyDelay = 10.0f;
};
