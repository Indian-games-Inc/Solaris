// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Flashlight.generated.h"

UCLASS()
class CRYPTRAIDER_API AFlashlight : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFlashlight();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void Toggle();

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Light, meta = (AllowPrivateAccess = "true"))
	class USpotLightComponent* SpotLight;
};
