// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SecurityMonitor.generated.h"

UCLASS()
class CRYPTRAIDER_API ASecurityMonitor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASecurityMonitor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Monitor;

private:
	UPROPERTY(EditAnywhere)
	class ASecurityCamera* LinkedCamera;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* MaterialInterface;
	
	UPROPERTY()
	UMaterialInstanceDynamic* CameraMaterial;

	UPROPERTY(EditDefaultsOnly)
	UTextureRenderTarget2D* CameraRenderTarget;

	UPROPERTY(EditAnywhere)
	float ScreenBrightness = 1.0;

	UPROPERTY(EditAnywhere)
	float ScreenQualityLevel = 1.0;
};
