// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseInteractible.h"
#include "GameFramework/Actor.h"
#include "DoorSwitchButton.generated.h"

UCLASS()
class CRYPTRAIDER_API ADoorSwitchButton : public ABaseInteractible
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADoorSwitchButton();

public:
	UFUNCTION(BlueprintCallable)
	virtual void Interact() override;

	virtual FString HintMessage() const override;

private:
	UPROPERTY(EditInstanceOnly)
	class ADoor* Door;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;
};
