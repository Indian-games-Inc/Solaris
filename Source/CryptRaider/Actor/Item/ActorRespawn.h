// Fill out your copyright notice in the Description page of Project Settings.

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
	// Sets default values for this actor's properties
	AActorRespawn();

	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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
