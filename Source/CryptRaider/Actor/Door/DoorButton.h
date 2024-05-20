// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Interface/BaseInteractible.h"
#include "GameFramework/Actor.h"
#include "DoorButton.generated.h"

UCLASS()
class CRYPTRAIDER_API ADoorButton : public AActor, public IInteractible
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADoorButton();

public:
	UFUNCTION(BlueprintCallable)
	virtual void Interact() override;

	virtual FString HintMessage() const override;

	virtual bool IsActive() const override;

protected:
	UPROPERTY(EditInstanceOnly)
	class ADoor* Door;
	
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* Mesh;

private:
	USceneComponent* Root = nullptr;
};
