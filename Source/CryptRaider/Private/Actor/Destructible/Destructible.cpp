// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Destructible/Destructible.h"
#include "TimerManager.h"
#include "GeometryCollection/GeometryCollectionComponent.h"

ADestructible::ADestructible()
{
	GetGeometryCollectionComponent()->bNotifyBreaks = true;
	GetGeometryCollectionComponent()->bNotifyGlobalBreaks = true;
	GetGeometryCollectionComponent()->OnChaosBreakEvent.AddDynamic(this, &ADestructible::OnBreakEvent);
}

void ADestructible::OnDestroy()
{
	GetGeometryCollectionComponent()->CrumbleActiveClusters();
	DisableCollision();

	FTimerHandle DestroyTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, this,
		&ADestructible::DelayedDestroy, DestroyDelay, false);
}

void ADestructible::OnBreakEvent(const FChaosBreakEvent& BreakEvent)
{
	// Can't set timers in delegates directly...
	// For some reason timers in delegates aren't working
	OnDestroy();
}

void ADestructible::DisableCollision()
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

