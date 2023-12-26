// Fill out your copyright notice in the Description page of Project Settings.

#include "Picker.h"
#include "Item.h"

// Sets default values for this component's properties
UPicker::UPicker()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UPicker::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UPicker::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

FItemData UPicker::PickItem()
{
	FHitResult HitResult;

	FVector Start = GetComponentLocation() + GetForwardVector();
	FVector End = Start + GetForwardVector() * 100;

	DrawDebugLine(GetWorld(), Start, End, FColor::Cyan);

	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);

	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult, Start, End,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		Sphere
	);


	if (HasHit)
	{
		auto* Item = Cast<AItem>(HitResult.GetActor());
		if (Item)
		{
			return Item->Pick();
		}
	}

	return {};
}
