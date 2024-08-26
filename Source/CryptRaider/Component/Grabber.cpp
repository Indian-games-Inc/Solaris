// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Hand.h"
#include "CryptRaider/Actor/Destructible/Projectile.h"
#include "CryptRaider/Player/BasePlayerController.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (auto* PhysicsHandle = GetPhysicsHandle();
		IsValid(PhysicsHandle) && IsValid(GetGrabbed()))
	{
		const FVector Location = GetHand()->GetComponentLocation();
		const FVector ForwardVector = GetHand()->GetForwardVector();

		const FRotator Rotation = GetHand()->GetComponentRotation();

		const FVector TargetLocation = Location + ForwardVector * HoldDistance;
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, Rotation);
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

	if (!PhysicsHandle)
	{
		return;
	}
	
	if (auto* Projectile = GetProjectileInReach(); IsValid(Projectile))
	{
		if (auto* Body = Projectile->GetBody(); IsValid(Body))
		{
			Body->WakeAllRigidBodies();
			Body->SetSimulatePhysics(true);
			Body->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap); // Disable collision with Pawns

			Projectile->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			Projectile->Tags.Add(GrabbedTag);

			PhysicsHandle->GrabComponentAtLocationWithRotation(
				Body,
				NAME_None,
				Projectile->GetActorLocation(),
				GetHand()->GetComponentRotation()
			);
			
			OnGrabbedUpdated.Broadcast(Projectile);
		}
	}
}

void UGrabber::Release()
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (!PhysicsHandle) { return; }

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
		Projectile->Charge();

		Release();

		if (auto* Body = Projectile->GetBody(); IsValid(Body))
		{
			const FVector ForwardVector = GetHand()->GetForwardVector();
			const FVector ImpulseVector = ForwardVector * ThrowImpulseStrength;
			Body->SetPhysicsLinearVelocity(ImpulseVector);
		}
	}
}

FText UGrabber::ConstructHint() const
{
	const auto* Controller = GetController();
	if (!IsValid(Controller))
		return {};

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
