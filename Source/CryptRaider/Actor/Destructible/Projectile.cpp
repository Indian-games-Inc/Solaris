// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "Destructible.h"
#include "Field/FieldSystemActor.h"

void AProjectile::OnComponentHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (auto* OtherDestructibleActor = Cast<ADestructible>(OtherActor); OtherDestructibleActor)
	{
		AddForce(Hit.Location);
	}

	bIsCharged = false;
}

void AProjectile::Interact()
{
	Super::Interact();
}

FString AProjectile::HintMessage() const
{
	return Tags.Contains(GrabbedTag) ? "Release" : "Grab";
}

bool AProjectile::IsCharged() const
{
	return bIsCharged;
}

void AProjectile::Charge()
{
	bIsCharged = true;
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
