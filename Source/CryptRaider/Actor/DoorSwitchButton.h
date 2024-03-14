// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CryptRaider/Interface/Interactible.h"
#include "GameFramework/Actor.h"
#include "DoorSwitchButton.generated.h"

UCLASS()
class CRYPTRAIDER_API ADoorSwitchButton : public AActor, public IInteractible
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADoorSwitchButton();

public:
	UFUNCTION(BlueprintCallable)
	void Interact() override;

private:
	UPROPERTY(EditInstanceOnly)
	class ADoor* Door;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;
};
