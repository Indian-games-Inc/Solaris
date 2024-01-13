// Fill out your copyright notice in the Description page of Project Settings.

#include "Picker.h"
#include "../Actor/Item.h"


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
