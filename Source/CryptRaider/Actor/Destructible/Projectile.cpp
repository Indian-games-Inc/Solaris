// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "Destructible.h"
#include "CryptRaider/AI/Common/BaseAICharacter.h"
#include "CryptRaider/Damage/Event/StunDamageEvent.h"
#include "Field/FieldSystemActor.h"

void AProjectile::OnComponentHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (IsValid(Cast<ADestructible>(OtherActor)))
	{
		AddForce(Hit.Location);
	}

	if (IsValid(Cast<ABaseAICharacter>(OtherActor)) && HitForceThreshold <= GetForce())
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Force: %f, Threshold: %f"), GetForce(), HitForceThreshold)
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

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	if (!Body) {
		UE_LOG(LogTemp, Warning, TEXT("Failed to bind OnComponentHit, Body isn't initialized"))
	}

	Body->OnComponentHit.AddDynamic(this, &AProjectile::OnComponentHit);
}

void AProjectile::AddForce(const FVector& Location) const
{
	AFieldSystemActor* MasterFieldActor = GetWorld()->SpawnActor<AFieldSystemActor>(
		MasterFieldClass,
		Location,
		FRotator::ZeroRotator
	);

	if (!MasterFieldActor) {
		UE_LOG(LogTemp, Warning, TEXT("Failed to spawn MasterField"));
		return;
	}
	
	MasterFieldActor->SetLifeSpan(MasterFieldDestructionDelay);
}

float AProjectile::GetForce() const // TODO calculate force toward hit location
{
	const float Mass = GetBody()->GetMass();
	const float Velocity = GetBody()->GetComponentVelocity().Size();

	UE_LOG(LogTemp, Warning, TEXT("Mass: %f"), Mass);
	UE_LOG(LogTemp, Warning, TEXT("Velocity: %f"), Velocity);

	return Mass * Velocity;
}
