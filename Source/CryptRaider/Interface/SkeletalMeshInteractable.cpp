// Fill out your copyright notice in the Description page of Project Settings.


#include "SkeletalMeshInteractable.h"

#include "CryptRaider/Player/BasePlayerController.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

ASkeletalMeshInteractable::ASkeletalMeshInteractable()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(RootComponent);

	CloseUpCamera = CreateDefaultSubobject<UCameraComponent>("CloseUpCamera");
	CloseUpCamera->SetupAttachment(Body);
}

//TODO: all code should be some where in SkeletalItem -> HidingBox

// Sets default values

void ASkeletalMeshInteractable::Interact()
{
	const auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (true)
	{
		Body->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
		this->SetActorRotation(FRotator(180.0f, 0.0f, 0.0f), ETeleportType::TeleportPhysics);
		PlayerController->SetViewTargetWithBlend(this, 0.1);
		PlayerController->GetPawn()->SetActorLocation(this->GetActorLocation());
		// Body->AttachToComponent(PlayerController->GetCharacter(), FAttachmentTransformRules::KeepWorldTransform);
	}
	else
	{
		//switch camera to player
		PlayerController->SetViewTargetWithBlend(PlayerController);
	}
}

//TODO: add message for escape from box
FString ASkeletalMeshInteractable::HintMessage() const
{
	return Tags.Contains(GrabbedTag) ? "Release" : "Grab | Hide";
}

bool ASkeletalMeshInteractable::IsActive() const
{
	return true;
}

void ASkeletalMeshInteractable::DisablePhysics() const
{
	Body->SetSimulatePhysics(false);
	Body->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Body->OnActorEnableCollisionChanged();
}

void ASkeletalMeshInteractable::EnablePhysics() const
{
	Body->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Body->OnActorEnableCollisionChanged();
}
