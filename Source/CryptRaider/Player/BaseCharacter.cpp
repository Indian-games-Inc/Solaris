// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

#include "BasePlayerController.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "CryptRaider/Actor/Projectile.h"
#include "CryptRaider/Component/Hand.h"
#include "CryptRaider/Component/Grabber.h"
#include "CryptRaider/Component/Picker.h"
#include "CryptRaider/Component/Interactor.h"
#include "CryptRaider/Data/InventoryItemWrapper.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(RootComponent);
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	SkeletalMeshComponent->SetupAttachment(FirstPersonCameraComponent);

	Hand = CreateDefaultSubobject<UHand>(TEXT("Hand"));
	Hand->SetupAttachment(FirstPersonCameraComponent);

	Grabber = CreateDefaultSubobject<UGrabber>(TEXT("Grabber"));
	Grabber->SetupAttachment(Hand);

	Picker = CreateDefaultSubobject<UPicker>(TEXT("Picker"));
	Picker->SetupAttachment(Hand);

	Interactor = CreateDefaultSubobject<UInteractor>(TEXT("Interactor"));
	Interactor->SetupAttachment(Hand);


}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (!Controller)
	{
		return;
	}

	if (!IsOnLadder)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
	else
	{
		GetCharacterMovement()->SetMovementMode(MOVE_Flying);
		AddMovementInput(GetActorUpVector(), MovementVector.Y);
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
	}
}

void ABaseCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ABaseCharacter::Jump()
{
	UnCrouch();
	Super::Jump();
}

void ABaseCharacter::OnCrouch()
{
	if (bIsCrouched)
	{
		UnCrouch();
	}
	else
	{
		Crouch();
	}
}

void ABaseCharacter::Grab()
{
	if (!Grabber) { return; }

	if (!Grabber->IsGrabbing())
	{
		if (const auto& HitResult = Hand->GetInteractableInReach(); HitResult.IsSet())
		{
			Grabber->Grab(HitResult.GetValue());
		}
	}
	else
	{
		Grabber->Release();
	}
}

void ABaseCharacter::Throw()
{
	if (Grabber)
		Grabber->Throw();
}

void ABaseCharacter::Interact()
{
	if (const auto& HitResult = Hand->GetInteractableInReach())
	{
		if (Interactor)
		{
			Interactor->Interact(HitResult.GetValue());
		}
	}
}

TOptional<FInventoryItemWrapper> ABaseCharacter::PickUp()
{
	if (const auto& HitResult = Hand->GetInteractableInReach())
	{
		if (Picker)
		{
			return Picker->PickItem(HitResult.GetValue());
		}
	}
	return {};
}

UGrabber* ABaseCharacter::GetGrabber() const
{
	return Grabber;
}

void ABaseCharacter::SetOnLadder(bool Value)
{
	IsOnLadder = Value;
}

FText ABaseCharacter::ConstructHintFor(const IInteractible* Interactible) const
{
	const auto* BaseController = Cast<ABasePlayerController>(GetController());
	if (!BaseController)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to contruct Hint message, failed to cast Player Controller"));
		return FText::FromString("");
	}
	
	TOptional<FKey> Key;
	if (Cast<AProjectile>(Interactible)) {
		Key = BaseController->GrabKey();
	} else {
		Key = BaseController->InteractKey();
	}

	if (!Key.IsSet())
		return FText::FromString("");
	
	const FString Result = FString::Printf(
		TEXT("[%s] %s"),
		*Key->ToString(),
		*Interactible->HintMessage()
	);
	return FText::FromString(Result);
}

FText ABaseCharacter::HintMessage() const
{
	if (!Hand)
	{
		return FText::GetEmpty();
	}
	
	if (TOptional<FHitResult> HitResult = Hand->GetInteractableInReach(); HitResult.IsSet())
	{
		if (const auto* Interactible = Cast<IInteractible>(HitResult->GetActor()); Interactible)
		{
			return ConstructHintFor(Interactible);
		}
	}
	return FText::GetEmpty();
}
