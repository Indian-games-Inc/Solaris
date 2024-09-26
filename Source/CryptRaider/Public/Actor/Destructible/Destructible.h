#pragma once

#include "CoreMinimal.h"
#include "Chaos/ChaosGameplayEventDispatcher.h"
#include "GameFramework/Actor.h"
#include "GeometryCollection/GeometryCollectionActor.h"
#include "Destructible.generated.h"

UCLASS()
class CRYPTRAIDER_API ADestructible : public AGeometryCollectionActor
{
	GENERATED_BODY()

public:
	ADestructible();
	
	virtual void OnDestroy();

private:
	UFUNCTION()
	virtual void OnBreakEvent(const FChaosBreakEvent& BreakEvent);
	
	void DisableCollision();

	UFUNCTION()
	void DelayedDestroy();

private:
	UPROPERTY(EditAnywhere)
	float DestroyDelay = 60.0f;
};
