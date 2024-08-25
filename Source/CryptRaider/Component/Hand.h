// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Misc/Optional.h"

#include "Hand.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UHand : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHand();

public:
	TOptional<FHitResult> GetInteractableInReach() const;
	TOptional<FHitResult> GetInteractableWithCoords(FVector Start, FVector End) const;

private:
	TOptional<FHitResult> LineTrace(FVector Start, FVector End, int Radius) const;

private:
	UPROPERTY(EditAnywhere)
	float MaxInteractDistance = 200;

	UPROPERTY(EditAnywhere)
	float InteractRadius = 20;
};
