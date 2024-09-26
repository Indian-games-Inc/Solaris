#include "Actor/Cameras/SecurityMonitor.h"
#include "Actor/Cameras/SecurityCamera.h"
#include "Engine/TextureRenderTarget2D.h"


ASecurityMonitor::ASecurityMonitor()
{
	Monitor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Monitor"));
	SetRootComponent(Monitor);

	CameraRenderTarget = CreateDefaultSubobject<UTextureRenderTarget2D>(TEXT("CameraRenderTarget"));
}

void ASecurityMonitor::BeginPlay()
{
	Super::BeginPlay();

	if (!LinkedCamera)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to link camera to monitor, camera isn't set"));
		return;
	}

	if (!MaterialInterface)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to create Camera material, material isn't set"));
		return;
	}

	CameraMaterial = UMaterialInstanceDynamic::Create(MaterialInterface, this);

	if (CameraMaterial)
	{
		if (Monitor)
		{
			Monitor->SetMaterial(0, CameraMaterial);
		}

		FVector2D Size;
		GetWorld()->GetGameViewport()->GetViewportSize(Size); // TODO: Use absolute scale?

		const int64 SizeX = FMath::TruncToInt(Size.X * ScreenQualityLevel);
		const int64 SizeY = FMath::TruncToInt(Size.Y * ScreenQualityLevel);

		if (CameraRenderTarget)
		{
			CameraRenderTarget->InitAutoFormat(SizeX, SizeY);

			LinkedCamera->SetTextureTarget(CameraRenderTarget);

			CameraMaterial->SetTextureParameterValue("Texture", CameraRenderTarget);
			CameraMaterial->SetScalarParameterValue("ScreenBrightness", ScreenBrightness);
		}
	}
}
