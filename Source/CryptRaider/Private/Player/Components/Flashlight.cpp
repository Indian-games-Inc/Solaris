#include "Player/Components/Flashlight.h"

#include "Components/SpotLightComponent.h"
#include "GameFramework/Character.h"


AFlashlight::AFlashlight()
{
	PrimaryActorTick.bCanEverTick = true;

	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	SpotLight->SetupAttachment(RootComponent);
}

void AFlashlight::BeginPlay()
{
	Super::BeginPlay();
	SpotLight->SetVisibility(false);
}

void AFlashlight::Toggle()
{
	if (SpotLight->GetVisibleFlag())
	{
		SpotLight->SetVisibility(false);
	}
	else
	{
		SpotLight->SetVisibility(true);
	}

	const auto* PlayerCharacter = GetWorld()->GetFirstPlayerController()->GetCharacter();
	MakeNoise(ToggleLoudness, PlayerCharacter->GetInstigator(), GetActorLocation());
}
