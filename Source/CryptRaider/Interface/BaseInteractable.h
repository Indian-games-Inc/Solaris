// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CryptRaider/Interface/Interactable.h"
#include "GameFramework/Actor.h"
#include "BaseInteractable.generated.h"

UCLASS()
class CRYPTRAIDER_API ABaseInteractable : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseInteractable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact() override;
	virtual FString HintMessage() const override;
	virtual bool IsActive() const override;

	void DisablePhysics() const;
	void EnablePhysics() const;

protected:
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Body;
};
