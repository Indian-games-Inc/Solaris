// Fill out your copyright notice in the Description page of Project Settings.


#include "SecurityCamera.h"

#include "NavigationSystemTypes.h"
#include "Components/SceneCaptureComponent2D.h"


// Sets default values
ASecurityCamera::ASecurityCamera()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneCaptureComponent2D = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCaptureComponent2D"));
	SceneCaptureComponent2D->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASecurityCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASecurityCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASecurityCamera::RotateCamera(float VerticalShift, float HorizontalShift)
{
	const FRotator CurrentRotation = SceneCaptureComponent2D->GetRelativeRotation();
	
	float NewPitch = FMath::Clamp(CurrentRotation.Pitch + (VerticalShift * VerticalSensitivity), MaxDownRotation, MaxUpRotation);
	float NewYaw = FMath::Clamp(CurrentRotation.Yaw + (HorizontalShift * HorizontalSensitivity), MaxLeftRotation, MaxRightRotation);

	SceneCaptureComponent2D->SetRelativeRotation({0, NewPitch, NewYaw});
}

void ASecurityCamera::SetTextureTarget(UTextureRenderTarget2D* TextureRenderTarget)
{
	SceneCaptureComponent2D->TextureTarget = TextureRenderTarget;
}
