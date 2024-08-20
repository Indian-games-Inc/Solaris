// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorRespawn.h"


// Sets default values
AActorRespawn::AActorRespawn()
{
	ChildActorComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("Actor"));
	RootComponent = ChildActorComponent;
	SetRootComponent(ChildActorComponent);
}

void AActorRespawn::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	RespawnActor();
}

// Called when the game starts or when spawned
void AActorRespawn::BeginPlay()
{
	Super::BeginPlay();
}

void AActorRespawn::OnItemDestroyed(AActor* DestroyedActor)
{
	GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle,
	                                       this, &AActorRespawn::RespawnActor,
	                                       RespawnDelay > 0 ? RespawnDelay : 0.1f);
}

void AActorRespawn::RespawnActor()
{
	if (IsValid(ChildActorComponent))
	{
		if (IsValid(ChildActorComponent->GetChildActor()))
		{
			ChildActorComponent->GetChildActor()->OnDestroyed.RemoveAll(this);
			ChildActorComponent->DestroyChildActor();
		}
	
		ChildActorComponent->CreateChildActor();
		if (IsValid(ChildActorComponent->GetChildActor()))
		{
			ChildActorComponent->GetChildActor()->OnDestroyed.AddDynamic(this, &AActorRespawn::OnItemDestroyed);	
		}
	}
}
