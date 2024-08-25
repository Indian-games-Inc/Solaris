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

	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (IsValid(PhysicsHandle) && IsValid(PhysicsHandle->GetGrabbedComponent()))
	{
		const FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}

	// TODO Add Hint clearing
	if (const auto& HintMessage = ConstructHintMessage(); !HintMessage.IsEmpty())
	{
		OnHintUpdated.Broadcast(ConstructHintMessage());	
	}
}

FText UGrabber::ConstructHintMessage() const
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
	if (const UHand* Hand = GetHand(); IsValid(Hand))
	{
		if (const auto& HitResult = Hand->GetInteractableInReach();
			HitResult.IsSet() && Cast<AProjectile>(HitResult->GetActor()))
		{
			return FText::FromString(FString::Printf(
				TEXT("[%s] Grab"),
				*Controller->GrabKey()->ToString()
			));
		}
	}
	return {};
}

UPrimitiveComponent* UGrabber::GetGrabbed() const
{
	if (const auto* PhysicsHandle = GetPhysicsHandle(); IsValid(PhysicsHandle))
	{
		return PhysicsHandle->GetGrabbedComponent();
	}
	return nullptr;
}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
	return GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
}

UHand* UGrabber::GetHand() const
{
	return GetOwner()->FindComponentByClass<UHand>();
}

ABasePlayerController* UGrabber::GetController() const
{
	if (const auto* Character = Cast<ACharacter>(GetOwner()); IsValid(Character))
	{
		return Cast<ABasePlayerController>(Character->GetController());
	}

	return nullptr;
}

void UGrabber::Grab(const FHitResult& HitResult) // TODO Refactor regarding GetHand()
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

	if (auto* Grabbed = GetGrabbed(); Grabbed)
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
	if (auto* Grabbed = GetGrabbed(); Grabbed)
	{
		if (auto* Projectile = Cast<AProjectile>(GetGrabbed()->GetOwner()); IsValid(Projectile))
		{
			Projectile->Charge();

			Release();
			
			const FVector ImpulseVector = GetForwardVector() * ThrowImpulseStrength;
			Grabbed->SetPhysicsLinearVelocity(ImpulseVector);
		}
	}
}

bool UGrabber::IsGrabbing() const // TODO Remove this shit too
{
	return GetGrabbed() != nullptr;
}

FString UGrabber::GetGrabbedItemName() const // TODO Remove this shit too
{
	return GetGrabbed()->GetOwner()->GetActorNameOrLabel();
}
