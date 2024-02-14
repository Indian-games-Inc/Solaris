// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileItem.h"

#include "Destructible.h"
#include "Field/FieldSystemActor.h"

void AProjectileItem::OnComponentHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
                                     UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (auto* OtherDestructibleActor = Cast<ADestructible>(OtherActor); OtherDestructibleActor)
	{
		AddForce(Hit.Location);

		OtherDestructibleActor->OnDestroy();
	}
}

void AProjectileItem::AddForce(const FVector& Location) const
{
	AFieldSystemActor* MasterFieldActor = GetWorld()->SpawnActor<AFieldSystemActor>(
		MasterFieldClass,
		Location,
		FRotator::ZeroRotator
	);

	MasterFieldActor->SetLifeSpan(MasterFieldDestructionDelay);
}
