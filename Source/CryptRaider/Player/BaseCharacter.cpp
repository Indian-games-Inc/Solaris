// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

#include "BasePlayerController.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "CryptRaider/Actor/Destructible/Projectile.h"
#include "CryptRaider/Actor/Door/DoorPinLock.h"
#include "CryptRaider/Component/Hand.h"
#include "CryptRaider/Component/Grabber.h"
#include "CryptRaider/Component/Picker.h"
#include "CryptRaider/Component/Interactor.h"
#include "CryptRaider/Data/InventoryItemWrapper.h"
#include "CryptRaider/GameMode/DefaultGameMode.h"
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
	Health = MaxHealth;
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
		if (PinLock != nullptr)
		{
			FVector WorldDirection;
			FVector Start = Cast<ABasePlayerController>(Controller)->GetWorldLocationFromCursor(WorldDirection);
			FVector End = Start + WorldDirection * 70;

			if (TOptional<FHitResult> HitResult = Hand->GetInteractableWithCoords(Start, End); HitResult.IsSet())
			{
				auto Hit = HitResult.GetValue();
				PinLock->SetLightPosition(Hit.Location - WorldDirection * 1.5);
			}
			return;
		}

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

float ABaseCharacter::TakeDamage(float Damage,
                                 const FDamageEvent& DamageEvent,
                                 AController* EventInstigator,
                                 AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;

	UE_LOG(LogTemp, Warning, TEXT("Damage applied, Health: %f"), Health);

	if (IsDead())
	{
		UE_LOG(LogTemp, Warning, TEXT("Oops you are dead"));
		if (ADefaultGameMode* GameMode = GetWorld()->GetAuthGameMode<ADefaultGameMode>(); GameMode)
		{
			GameMode->PawnKilled(this);
		}
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	return DamageToApply;
}

bool ABaseCharacter::IsDead() const
{
	return Health <= 0;
}

float ABaseCharacter::GetHealthPercent() const
{
	return Health / MaxHealth;
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
	if (Cast<AProjectile>(Interactible))
	{
		Key = BaseController->GrabKey();
	}
	else
	{
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

void ABaseCharacter::InteractWithPinLock(FVector& Start, FVector& End)
{
	if (TOptional<FHitResult> HitResult = Hand->GetInteractableWithCoords(Start, End); HitResult.IsSet())
	{
		auto Hit = HitResult.GetValue();
		UE_LOG(LogTemp, Warning, TEXT("B: %s"), *Hit.BoneName.ToString());
		PinLock->PressButton(Hit.BoneName.ToString());
	}
}

void ABaseCharacter::SetOnLadder(bool Value)
{
	IsOnLadder = Value;
}

/** Pin code part **/
void ABaseCharacter::SetPinLock(ADoorPinLock* PinLockRef)
{
	PinLock = PinLockRef;
	const auto PlayerController = Cast<ABasePlayerController>(GetController());
	PlayerController->SetIgnoreMoveInput(PinLock != nullptr);
	if (PinLock)
	{
		//switch camera to pin lock
		PlayerController->SetViewTargetWithBlend(PinLock, 0.1);
	}
	else
	{
		//switch camera to player
		PlayerController->SetViewTargetWithBlend(this);
	}
}

bool ABaseCharacter::IsInPinLock() const
{
	return PinLock ? true : false;
}

void ABaseCharacter::MouseClick()
{
	if (PinLock)
	{
		FVector WorldDirection;
		FVector Start = Cast<ABasePlayerController>(GetController())->GetWorldLocationFromCursor(WorldDirection);
		FVector End = Start + WorldDirection * 70;
		InteractWithPinLock(Start, End);
	}
}
