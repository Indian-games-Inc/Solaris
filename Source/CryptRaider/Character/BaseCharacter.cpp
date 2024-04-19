// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "CryptRaider/Actor/Destructible/Projectile.h"
#include "CryptRaider/Actor/Door/DoorPinLock.h"
#include "CryptRaider/Component/Hand.h"
#include "CryptRaider/Component/Grabber.h"
#include "CryptRaider/Component/Picker.h"
#include "CryptRaider/Component/Interactor.h"
#include "CryptRaider/Component/Inventory.h"
#include "CryptRaider/Data/InventoryItemWrapper.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"

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

	Inventory = CreateDefaultSubobject<UInventory>(TEXT("Inventory"));
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Look);

		// Crouching
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &ABaseCharacter::OnCrouch);

		// Interaction with world
		EnhancedInputComponent->BindAction(GrabAction, ETriggerEvent::Started, this, &ABaseCharacter::Grab);
		EnhancedInputComponent->BindAction(ThrowAction, ETriggerEvent::Started, this, &ABaseCharacter::Throw);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ABaseCharacter::Interact);

		//Mouse handling for PinLocks
		EnhancedInputComponent->BindAction(MouseClickAction, ETriggerEvent::Started, this, &ABaseCharacter::MouseClick);
	}
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

FVector ABaseCharacter::GetWorldLocationFromCursor(FVector& WorldDirection)
{
	FVector WorldLocation;
	const auto PlayerController = Cast<APlayerController>(Controller);
	PlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);
	return WorldLocation;
}

void ABaseCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		if (PinLock)
		{
			FVector WorldDirection;
			FVector Start = GetWorldLocationFromCursor(WorldDirection);
			FVector End = Start + WorldDirection * 70;

			if (TOptional<FHitResult> HitResult = Hand->GetInteractableInReach(Start, End); HitResult.IsSet())
			{
				auto Hit = HitResult.GetValue();
				PinLock->SetLightPosition(Hit.Location);
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

void ABaseCharacter::OnCrouch(const FInputActionValue& Value)
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

void ABaseCharacter::Grab(const FInputActionValue& Value)
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

void ABaseCharacter::Throw(const FInputActionValue& Value)
{
	if (Grabber)
		Grabber->Throw();
}

void ABaseCharacter::Interact(const FInputActionValue& Value)
{
	if (const auto& HitResult = Hand->GetInteractableInReach())
	{
		if (Interactor)
		{
			Interactor->Interact(HitResult.GetValue());
		}

		PickUp(HitResult.GetValue());
	}
}

void ABaseCharacter::PickUp(const FHitResult& HitResult)
{
	if (Picker)
	{
		if (Inventory->IsFull())
			return;

		if (const auto& Item = Picker->PickItem(HitResult))
		{
			Inventory->AddItem(Item.GetValue());
		}
	}
}

UGrabber* ABaseCharacter::GetGrabber() const
{
	return Grabber;
}

UInventory* ABaseCharacter::GetInventory() const
{
	return Inventory;
}

void ABaseCharacter::SetOnLadder(bool Value)
{
	IsOnLadder = Value;
}

TOptional<FKey> ABaseCharacter::GetKeyByAction(const UInputAction* Action) const
{
	// TODO: not the best logic, but at least it does its work, refactor in future 
	for (const FEnhancedActionKeyMapping& Mapping : DefaultMappingContext->GetMappings())
	{
		if (Mapping.Action.Get() == Action)
		{
			return Mapping.Key;
		}
	}
	return NullOpt;
}

FText ABaseCharacter::ConstructHintFor(const IInteractible* Interactible) const
{
	const UInputAction* Action;
	if (Cast<AProjectile>(Interactible))
	{
		Action = GrabAction;
	}
	else
	{
		Action = InteractAction;
	}

	if (const auto& Key = GetKeyByAction(Action))
	{
		const FString Result = FString::Printf(
			TEXT("[%s] %s"),
			*Key->ToString(),
			*Interactible->HintMessage()
		);
		return FText::FromString(Result);
	}

	return FText::FromString("");
}

FText ABaseCharacter::HintMessage() const
{
	if (!Hand)
	{
		return FText::GetEmpty();
	}

	const auto& Mappings = DefaultMappingContext->GetMappings();

	if (TOptional<FHitResult> HitResult = Hand->GetInteractableInReach(); HitResult.IsSet())
	{
		if (const auto* Interactible = Cast<IInteractible>(HitResult->GetActor()); Interactible)
		{
			return ConstructHintFor(Interactible);
		}
	}
	return FText::GetEmpty();
}

/** Pin code part **/
void ABaseCharacter::SetPinLock(ADoorPinLock* PinLockRef)
{
	PinLock = PinLockRef;
	Controller->SetIgnoreMoveInput(PinLock != nullptr);
	const auto PlayerController = Cast<APlayerController>(Controller);
	if (PinLock)
	{
		//switch camera to pin lock
		PlayerController->SetViewTargetWithBlend(PinLock, 0.1);
	}
	else
	{
		//switch camera to player
		Cast<APlayerController>(Controller)->SetViewTargetWithBlend(this);
	}
}

bool ABaseCharacter::IsInPinLock() const
{
	return PinLock ? true : false;
}

void ABaseCharacter::MouseClick(const FInputActionValue& Value)
{
	if (PinLock)
	{
		FVector WorldDirection;
		FVector Start = GetWorldLocationFromCursor(WorldDirection);
		FVector End = Start + WorldDirection * 70;
		if (TOptional<FHitResult> HitResult = Hand->GetInteractableInReach(Start, End); HitResult.IsSet())
		{
			auto Hit = HitResult.GetValue();
			UE_LOG(LogTemp, Warning, TEXT("B: %s"), *Hit.BoneName.ToString());
			PinLock->PressButton(Hit.BoneName.ToString());
		}
	}
}
