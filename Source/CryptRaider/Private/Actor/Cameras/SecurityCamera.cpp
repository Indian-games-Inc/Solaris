// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Cameras/SecurityCamera.h"

#include "Components/SceneCaptureComponent2D.h"


// Sets default values
ASecurityCamera::ASecurityCamera()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneCaptureComponent2D = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCaptureComponent2D"));
}

// Called when the game starts or when spawned
void ASecurityCamera::BeginPlay()
{
	Super::BeginPlay();
	
	RelativeStartRotation = SceneCaptureComponent2D->GetRelativeRotation();
}

// Called every frame
void ASecurityCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RotationTick();
}

void ASecurityCamera::RotateCamera(const float VerticalShift, const float HorizontalShift)
{
	const FRotator CurrentRotation = SceneCaptureComponent2D->GetRelativeRotation();
	
	const float NewPitch = FMath::Clamp(
		CurrentRotation.Pitch + (VerticalShift * VerticalSensitivity),
		RelativeStartRotation.Pitch + MaxDownRotation,
		RelativeStartRotation.Pitch + MaxUpRotation
	);
	const float NewYaw = FMath::Clamp(
		CurrentRotation.Yaw + (HorizontalShift * HorizontalSensitivity),
		RelativeStartRotation.Yaw + MaxLeftRotation,
		RelativeStartRotation.Yaw + MaxRightRotation
	);

	const FRotator NewRotation {
		FMath::TruncateToHalfIfClose(NewPitch),
		FMath::TruncateToHalfIfClose(NewYaw),
		0
	};
	
	SceneCaptureComponent2D->SetRelativeRotation(NewRotation);
}

void ASecurityCamera::SetTextureTarget(UTextureRenderTarget2D* TextureRenderTarget)
{
	SceneCaptureComponent2D->TextureTarget = TextureRenderTarget;
}

void ASecurityCamera::RotationTick()
{
	if (EnableMovement)
	{
		const FRotator CurrentRotation = SceneCaptureComponent2D->GetRelativeRotation();

		const float RightEdge = RelativeStartRotation.Yaw + MaxRightRotation;
		const float LeftEdge  = RelativeStartRotation.Yaw + MaxLeftRotation;

		const bool IsOnRightEdge = RightEdge <= CurrentRotation.Yaw;
		const bool IsOnLeftEdge  = LeftEdge  >= CurrentRotation.Yaw;
		
		if (IsOnRightEdge) {
			IsRightMoveDirection = false;
		}
		else if (IsOnLeftEdge) {
			IsRightMoveDirection = true;
		}
		
		if (IsRightMoveDirection) {
			RotateCamera(0, 1);
		}
		else {
			RotateCamera(0, -1);
		}
	}
}
