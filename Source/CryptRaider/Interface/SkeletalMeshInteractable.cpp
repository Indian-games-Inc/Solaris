// Fill out your copyright notice in the Description page of Project Settings.


#include "SkeletalMeshInteractable.h"

#include "CryptRaider/Player/BasePlayerController.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ASkeletalMeshInteractable::ASkeletalMeshInteractable()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(RootComponent);

	CloseUpCamera = CreateDefaultSubobject<UCameraComponent>("CloseUpCamera");
	CloseUpCamera->SetupAttachment(Body);


	// Bind the OnHit function
	// Body->OnComponentHit.AddDynamic(this, &AStaticMeshInteractable::OnHit);
}

void ASkeletalMeshInteractable::Interact()
{
	const auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (true)
	{
		this->SetActorRotation(FRotator(180.0f, 0.0f, 0.0f), ETeleportType::TeleportPhysics);
		PlayerController->SetViewTargetWithBlend(this, 0.1);
	}
	else
	{
		//switch camera to player
		PlayerController->SetViewTargetWithBlend(PlayerController);
	}
}

FString ASkeletalMeshInteractable::HintMessage() const
{
	return Tags.Contains(GrabbedTag) ? "Release" : "Grab | Hide";
}

bool ASkeletalMeshInteractable::IsActive() const
{
	return true;
}

// Called when the game starts or when spawned
void ASkeletalMeshInteractable::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASkeletalMeshInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
