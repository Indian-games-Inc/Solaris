// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "CryptRaider/Actor/Destructible/Projectile.h"
#include "CryptRaider/Actor/Item/Item.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle && PhysicsHandle->GetGrabbedComponent())
	{
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}
}

UPrimitiveComponent* UGrabber::GetGrabbedItem() const
{
	if (const auto* PhysicsHandle = GetPhysicsHandle(); PhysicsHandle)
	{
		return PhysicsHandle->GetGrabbedComponent();
	}

	return nullptr;
}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
	return GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
}

void UGrabber::Grab(const FHitResult& HitResult)
{
	if (const auto* Projectile = Cast<AProjectile>(HitResult.GetActor()); !Projectile)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to Grab actor, it's not a Projectile"));
		return;
	}

	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (!PhysicsHandle)
		return;

	UPrimitiveComponent* HitComponent = HitResult.GetComponent();
	HitComponent->WakeAllRigidBodies();
	HitComponent->SetSimulatePhysics(true);
	HitComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap); // Disable collision with Pawns

	auto* Actor = HitResult.GetActor();
	Actor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	Actor->Tags.Add(GrabbedTag);

	PhysicsHandle->GrabComponentAtLocationWithRotation(
		HitComponent,
		NAME_None,
		HitResult.ImpactPoint,
		GetComponentRotation()
	);
}

void UGrabber::Release()
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (!PhysicsHandle) { return; }

	if (auto* Grabbed = GetGrabbedItem(); Grabbed)
	{
		AActor* Actor = Grabbed->GetOwner();
		Actor->Tags.Remove(GrabbedTag);

		// Enable collision with Pawns back
		Grabbed->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);


		// Remove inertia from object
		Grabbed->SetPhysicsLinearVelocity(FVector::Zero());
		Grabbed->SetPhysicsAngularVelocityInDegrees(FVector::Zero());

		PhysicsHandle->ReleaseComponent();
	}
}

void UGrabber::Throw()
{
	if (auto* Grabbed = GetGrabbedItem(); Grabbed)
	{
		if (auto* Projectile = Cast<AProjectile>(GetGrabbedItem()->GetOwner()); IsValid(Projectile))
		{
			Projectile->Charge();

			Release();
			
			const FVector ImpulseVector = GetForwardVector() * ThrowImpulseStrength;
			Grabbed->SetPhysicsLinearVelocity(ImpulseVector);
		}
	}
}

bool UGrabber::IsGrabbing() const
{
	return GetGrabbedItem() != nullptr;
}

FString UGrabber::GetGrabbedItemName() const
{
	return GetGrabbedItem()->GetOwner()->GetActorLabel();
}
