// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Components/Flashlight.h"

#include "Components/SpotLightComponent.h"
#include "GameFramework/Character.h"


// Sets default values
AFlashlight::AFlashlight()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	SpotLight->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AFlashlight::BeginPlay()
{
	Super::BeginPlay();
	SpotLight->SetVisibility(false);
}

// Called every frame
void AFlashlight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
