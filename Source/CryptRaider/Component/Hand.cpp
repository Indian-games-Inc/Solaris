// Fill out your copyright notice in the Description page of Project Settings.


#include "Hand.h"

// Sets default values for this component's properties
UHand::UHand()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UHand::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UHand::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UHand::HasInteractableOnSight() const
{
	return GetInteractableInReach().IsSet();
}

TOptional<FHitResult> UHand::GetInteractableInReach() const
{
	FHitResult HitResult;

	FVector Start = GetComponentLocation() + GetForwardVector();
	FVector End = Start + GetForwardVector() * MaxInteractDistance;

	FCollisionShape Sphere = FCollisionShape::MakeSphere(InteractRadius);

	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult, Start, End,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		Sphere
	);

	if (HasHit)
	{
		// for debug purposes
		// DrawDebugLine(GetWorld(), Start, End, FColor::Red, true, 1.0f, 0, 1.0f);
		return HitResult;
	}

	return {};
}

TOptional<FHitResult> UHand::GetInteractableInReach(FVector Start, FVector End) const
{
	FCollisionShape Sphere = FCollisionShape::MakeSphere(0.5);
	FHitResult HitResult;
	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult, Start, End,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		Sphere
	);

	if (HasHit)
	{
		// for debug purposes
		// DrawDebugLine(GetWorld(), Start, End, FColor::Red, true, 1.0f, 0, 1.0f);
		return HitResult;
	}

	return {};
}
