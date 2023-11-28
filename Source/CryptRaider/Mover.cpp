// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();
	
	OriginalLocation = GetOwner()->GetActorLocation();

	// ...
	
}

void UMover::MoveActorTo(const FVector& TargetLocation, float DeltaTime)
{
	FVector CurrentLocation = GetOwner()->GetActorLocation();
	float Speed = FVector::Distance(CurrentLocation, TargetLocation) / MoveTime;

	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);

	GetOwner()->SetActorLocation(NewLocation);
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UE_LOG(LogTemp, Warning, TEXT("Moving owner: %s"), *GetOwner()->GetActorNameOrLabel());
	if (ShouldMove) {
		UE_LOG(LogTemp, Warning, TEXT("Moving to: %s"), *OriginalLocation.ToCompactString());
		MoveActorTo(OriginalLocation + MoveOffset, DeltaTime);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("Moving back to: %s"), *OriginalLocation.ToCompactString());
		MoveActorTo(OriginalLocation, DeltaTime);
	}
}

void UMover::SetShouldMove(bool Status)
{
	ShouldMove = Status;
}

