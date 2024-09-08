// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "Destructible.h"
#include "CryptRaider/Damage/Event/StunDamageEvent.h"
#include "Field/FieldSystemActor.h"

void AProjectile::OnComponentHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (IsValid(Cast<ADestructible>(OtherActor)))
	{
		AddForce(Hit.Location);
	}

	if (HitForceThreshold <= GetImpulse(Hit))
	{
		FStunDamageEvent DamageEvent;
		DamageEvent.StunDuration = StunDuration;
		DamageEvent.HitInfo = Hit;
		
		OtherActor->TakeDamage(1, DamageEvent, nullptr, this);
	}
}

void AProjectile::Interact()
{
	Super::Interact();
}

FString AProjectile::HintMessage() const
{
	return Tags.Contains(GrabbedTag) ? "Release" : "Grab";
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentVelocity = GetBody()->GetComponentVelocity();
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	if (auto* Body = GetBody(); IsValid(Body))
	{
		Body->OnComponentHit.AddDynamic(this, &AProjectile::OnComponentHit);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to bind OnComponentHit, Body isn't initialized"))
	}
}

void AProjectile::AddForce(const FVector& Location) const
{
	AFieldSystemActor* MasterFieldActor = GetWorld()->SpawnActor<AFieldSystemActor>(
		MasterFieldClass,
		Location,
		FRotator::ZeroRotator
	);

	if (!MasterFieldActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to spawn MasterField"));
		return;
	}

	MasterFieldActor->SetLifeSpan(MasterFieldDestructionDelay);
}

float AProjectile::GetImpulse(const FHitResult& HitResult) const
{
	const FVector BodyCenter = GetBody()->GetCenterOfMass();
	const FVector ImpactNormal = (HitResult.ImpactPoint - BodyCenter).GetSafeNormal();
	
	const float Mass = GetBody()->GetMass();

	// Division is needed to convert (centimeters / seconds) to (meters / second)
	const float NormalVelocity = FVector::DotProduct(CurrentVelocity, ImpactNormal) / 100;

	const float Impulse = Mass * NormalVelocity;

	// Debug Purpose only
	// DrawDebugLine(
	// 	GetWorld(),
	// 	BodyCenter,
	// 	BodyCenter + CurrentVelocity,
	// 	FColor::Yellow, false, 3
	// );
	// DrawDebugLine(GetWorld(),
	//               BodyCenter,
	//               BodyCenter + ImpactNormal * NormalVelocity,
	//               FColor::Red, false, 3);

	return Impulse;
}
