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

private:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Monitor;

private: // Components
	UPROPERTY(EditAnywhere)
	class ASecurityCamera* LinkedCamera;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* MaterialInterface;
	
	UPROPERTY()
	UMaterialInstanceDynamic* CameraMaterial;

	UPROPERTY(EditDefaultsOnly)
	UTextureRenderTarget2D* CameraRenderTarget;

private: // Properties
	UPROPERTY(EditAnywhere, Category="Monitor Properties")
	float ScreenBrightness = 1.0;

	UPROPERTY(EditAnywhere, Category="Monitor Properties")
	float ScreenQualityLevel = 1.0;
};
