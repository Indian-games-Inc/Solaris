#include "Actor/Item/ActorRespawn.h"


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
