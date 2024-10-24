#include "Player/Components/Grabber.h"

#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Player/Components/Hand.h"
#include "Actor/Destructible/Projectile.h"
#include "Player/BasePlayerController.h"


UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	auto* PhysicsHandle = GetPhysicsHandle();
	auto* Projectile = GetGrabbed();
	
	if (IsValid(PhysicsHandle) && IsValid(Projectile))
	{
		const FVector Location = GetHand()->GetComponentLocation();
		const FVector ForwardVector = GetHand()->GetForwardVector();
		const FRotator Rotation = GetHand()->GetComponentRotation();

		const FVector TargetLocation = Location + ForwardVector * HoldDistance;
	
		if (const float Distance = FVector::Distance(Projectile->GetActorLocation(), TargetLocation);
			Distance > ReleaseDistance)
		{
			Release();
		}
		else
		{
			PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, Rotation);	
		}
	}
}

void UGrabber::Interact()
{
	if (IsValid(GetGrabbed()))
	{
		Release();
	}
	else
	{
		Grab();
	}
}

void UGrabber::Grab()
{
	auto* PhysicsHandle = GetPhysicsHandle();

	if (!IsValid(PhysicsHandle)) { return; }
	
	if (auto* Projectile = GetProjectileInReach(); IsValid(Projectile))
	{
		if (auto* Body = Projectile->GetBody(); IsValid(Body))
		{
			PhysicsHandle->SetInterpolationSpeed(GetInterpSpeed(Body->GetMass()));
			
			Body->WakeAllRigidBodies();
			Body->SetSimulatePhysics(true);
			Body->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap); // Disable collision with Pawns

			Projectile->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			Projectile->Tags.Add(GrabbedTag);

			PhysicsHandle->GrabComponentAtLocationWithRotation(
				Body,
				NAME_None,
				Projectile->GetBody()->GetCenterOfMass(),
				GetHand()->GetComponentRotation()
			);
			
			OnGrabbedUpdated.Broadcast(Projectile);
		}
	}
}

void UGrabber::Release()
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (!IsValid(PhysicsHandle)) { return; }

	if (auto* Projectile = GetGrabbed(); Projectile)
	{
		Projectile->Tags.Remove(GrabbedTag);

		if (auto* Body = Projectile->GetBody(); IsValid(Body))
		{
			// Enable collision with Pawns back
			Body->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);

			// Remove inertia from object
			Body->SetPhysicsLinearVelocity(FVector::Zero());
			Body->SetPhysicsAngularVelocityInDegrees(FVector::Zero());
		}

		PhysicsHandle->ReleaseComponent();

		OnGrabbedUpdated.Broadcast(nullptr);
	}
}

void UGrabber::Throw()
{
	if (auto* Projectile = GetGrabbed(); IsValid(Projectile))
	{
		Release();

		if (auto* Body = Projectile->GetBody(); IsValid(Body))
		{
			const FVector ForwardVector = GetHand()->GetForwardVector();
			const FVector ImpulseVector = ForwardVector * GetThrowVelocity(Body->GetMass());
			
			Body->SetPhysicsLinearVelocity(ImpulseVector);
		}
	}
}

FText UGrabber::ConstructHint() const
{
	const auto* Controller = GetController();

	if (!IsValid(Controller)) { return {}; }

	if (IsValid(GetGrabbed()))
	{
		return FText::FromString(
			FString::Printf(
				TEXT("[%s] Release, [%s] Throw"),
				*Controller->GrabKey()->ToString(),
				*Controller->ThrowKey()->ToString()
			));
	}
	if (const auto* Projectile = GetProjectileInReach(); IsValid(Projectile))
	{
		return FText::FromString(FString::Printf(
			TEXT("[%s] Grab"),
			*Controller->GrabKey()->ToString()
		));
	}
	return {};
}

AProjectile* UGrabber::GetProjectileInReach() const
{
	if (const UHand* Hand = GetHand(); IsValid(Hand))
	{
		if (const auto& HitResult = Hand->GetInteractableInReach();
			HitResult.IsSet())
		{
			return Cast<AProjectile>(HitResult->GetActor());
		}
	}
	return {};
}

AProjectile* UGrabber::GetGrabbed() const
{
	if (const auto* PhysicsHandle = GetPhysicsHandle(); IsValid(PhysicsHandle))
	{
		if (const auto* Component = PhysicsHandle->GetGrabbedComponent(); IsValid(Component))
		{
			return Cast<AProjectile>(Component->GetOwner());
		}
	}
	return nullptr;
}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
	return GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
}

float UGrabber::GetInterpSpeed(const float& Mass) const
{
	return FMath::Max(
		MinInterpSpeed,
		FMath::Min(MaxInterpSpeed, InterpSpeedConstant / Mass)
	);
}

float UGrabber::GetThrowVelocity(const float& Mass) const
{
	return MinThrowVelocity
		+ (MaxThrowVelocity - MinThrowVelocity) / MaxObjectMass
		* FMath::Max(MaxObjectMass - Mass, 1.f);;
}
