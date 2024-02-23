// Fill out your copyright notice in the Description page of Project Settings.

#include "Picker.h"
#include "../Actor/Item.h"


FItemData UPicker::PickItem()
{
	FHitResult HitResult;
	if (GetPickableInReach(HitResult))
	{
		auto* Item = Cast<AItem>(HitResult.GetActor());
		if (Item)
		{
			return Item->Pick();
		}
	}

	return {};
}

bool UPicker::GetPickableInReach(FHitResult& HitResult) const
{
	FVector Start = GetComponentLocation() + GetForwardVector();
	FVector End = Start + GetForwardVector() * MaxPickDistance;

	FCollisionShape Sphere = FCollisionShape::MakeSphere(PickRadius);

	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult, Start, End,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		Sphere
	);

	return HasHit;
}

bool UPicker::HasItemNear()
{
	FHitResult HitResult;
	return GetPickableInReach(HitResult);
}
