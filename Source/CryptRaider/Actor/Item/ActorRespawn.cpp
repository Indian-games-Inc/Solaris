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

void AActorRespawn::OnActorDestroyed(AActor* DestroyedActor)
{
	const float RespawnDelayRate = RespawnDelay > 0 ? RespawnDelay : 0.1f;
	GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle,
	                                       this, &AActorRespawn::RespawnActor,
	                                       RespawnDelayRate);
}

void AActorRespawn::RespawnActor()
{
	if (IsValid(ChildActorComponent))
	{
		ChildActorComponent->DestroyChildActor();
		ChildActorComponent->CreateChildActor();

		if (auto* Actor = ChildActorComponent->GetChildActor(); IsValid(Actor))
		{
			Actor->OnDestroyed.AddDynamic(this, &AActorRespawn::OnActorDestroyed);	
		}
	}
}
