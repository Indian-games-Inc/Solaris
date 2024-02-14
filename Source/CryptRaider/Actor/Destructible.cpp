// Fill out your copyright notice in the Description page of Project Settings.


#include "Destructible.h"
#include "TimerManager.h"
#include "GeometryCollection/GeometryCollectionComponent.h"

void ADestructible::OnDestroy()
{
	FTimerHandle CollisionDisableTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(CollisionDisableTimerHandle, this,
		&ADestructible::DelayedDisableCollision, CollisionDisableDelay, false);

	FTimerHandle DestroyTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, this,
		&ADestructible::DelayedDestroy, DestroyDelay, false);
}

// Called when the game starts or when spawned
void ADestructible::BeginPlay()
{
	Super::BeginPlay();
}

void ADestructible::DelayedDisableCollision()
{
	FCollisionResponseContainer CollisionResponses;
	
	CollisionResponses.SetResponse(ECC_Pawn, ECR_Ignore);
	CollisionResponses.SetResponse(ECC_WorldDynamic, ECR_Ignore);

	GeometryCollectionComponent->SetCollisionResponseToChannels(CollisionResponses);
	GeometryCollectionComponent->OnActorEnableCollisionChanged();
}

void ADestructible::DelayedDestroy()
{
	Destroy();
}

