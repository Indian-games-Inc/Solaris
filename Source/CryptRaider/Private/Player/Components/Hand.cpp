#include "Player/Components/Hand.h"


UHand::UHand()
{
	PrimaryComponentTick.bCanEverTick = true;
}

TOptional<FHitResult> UHand::LineTrace(FVector Start, FVector End, int Radius) const
{
	FHitResult HitResult;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(Radius);

	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult, Start, End,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		Sphere
	);

	if (HasHit)
	{
		// for debug purposes
		// DrawDebugCylinder(GetWorld(), Start, End, Radius, 10, FColor::Cyan, false, 1.f);
		return HitResult;
	}

	return {};
}

TOptional<FHitResult> UHand::GetInteractableInReach() const
{
	FVector Start = GetComponentLocation() + GetForwardVector();
	FVector End = Start + GetForwardVector() * MaxInteractDistance;
	return LineTrace(Start, End, InteractRadius);
}

TOptional<FHitResult> UHand::GetInteractableWithCoords(FVector Start, FVector End) const
{
	return LineTrace(Start, End, 0.5f);
}
