#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SecurityCamera.generated.h"

UCLASS()
class CRYPTRAIDER_API ASecurityCamera : public AActor
{
	GENERATED_BODY()

public:
	ASecurityCamera();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void RotateCamera(const float VerticalShift, const float HorizontalShift);

public:
	void SetTextureTarget(UTextureRenderTarget2D* TextureRenderTarget);

private:
	void RotationTick();
	
private:
	UPROPERTY(EditAnywhere)
	USceneCaptureComponent2D* SceneCaptureComponent2D;

private:
	UPROPERTY(EditAnywhere, Category="Camera Properties")
	bool EnableMovement = false;
	
	UPROPERTY(EditAnywhere, Category="Camera Properties")
	float VerticalSensitivity = 1.0;

	UPROPERTY(EditAnywhere, Category="Camera Properties")
	float HorizontalSensitivity = 1.0;

	UPROPERTY(EditAnywhere, Category="Camera Properties")
	float MaxRightRotation = 45;

	UPROPERTY(EditAnywhere, Category="Camera Properties")
	float MaxLeftRotation = -45;

	UPROPERTY(EditAnywhere, Category="Camera Properties")
	float MaxUpRotation = 15;

	UPROPERTY(EditAnywhere, Category="Camera Properties")
	float MaxDownRotation = -45;

private:
	FRotator RelativeStartRotation;
	bool IsRightMoveDirection = true;
};
