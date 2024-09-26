#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "ActorRespawn.generated.h"


class ABaseInteractable;


UCLASS()
class CRYPTRAIDER_API AActorRespawn : public AActor
{
	GENERATED_BODY()

public:
	AActorRespawn();

	virtual void OnConstruction(const FTransform& Transform) override;

private:
	UFUNCTION()
	void OnActorDestroyed(AActor* DestroyedActor);

	void RespawnActor();
	
private:
	UPROPERTY(EditInstanceOnly, DisplayName="Actor", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UChildActorComponent> ChildActorComponent;

	UPROPERTY(EditAnywhere, Category = "Respawn", DisplayName="Delay", meta = (AllowPrivateAccess = "true"))
	float RespawnDelay;
	
	UPROPERTY()
	FTimerHandle RespawnTimerHandle;
};
