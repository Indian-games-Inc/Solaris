// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CryptRaider/Interface/Interactible.h"
#include "GameFramework/Actor.h"
#include "BaseInteractible.generated.h"

UCLASS()
class CRYPTRAIDER_API ABaseInteractible : public AActor, public IInteractible
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseInteractible();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact() override;

	void DisablePhysics() const;
	void EnablePhysics() const;

protected:
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Body;
};
