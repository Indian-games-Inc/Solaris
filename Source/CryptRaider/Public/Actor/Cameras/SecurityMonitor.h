#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SecurityMonitor.generated.h"

UCLASS()
class CRYPTRAIDER_API ASecurityMonitor : public AActor
{
	GENERATED_BODY()

public:
	ASecurityMonitor();

protected:
	virtual void BeginPlay() override;

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

private:
	UPROPERTY(EditAnywhere, Category="Monitor Properties")
	float ScreenBrightness = 1.0;

	UPROPERTY(EditAnywhere, Category="Monitor Properties")
	float ScreenQualityLevel = 1.0;
};
