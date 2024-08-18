// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "BaseCharacter.h"
#include "CryptRaider/Component/Inventory.h"

ABasePlayerController::ABasePlayerController()
{
	Inventory = CreateDefaultSubobject<UInventory>(TEXT("Inventory"));
}

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetupInput();
}

void ABasePlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}

void ABasePlayerController::SetupInput()
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		if (auto* BaseCharacter = Cast<ABaseCharacter>(GetCharacter()); IsValid(BaseCharacter))
		{
			if (auto* Movement = BaseCharacter->GetMovement(); IsValid(Movement))
			{
				//Movement
				EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, Movement,
				                                   &UMovement::Jump);
				//Moving
				EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, Movement,
				                                   &UMovement::Move);
				// Crouching
				EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, Movement,
				                                   &UMovement::Crouch);
				// Sprinting
				EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, Movement,
				                                   &UMovement::StartSprint);
				EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, Movement,
				                                   &UMovement::StopSprint);
			}
			//Looking
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, BaseCharacter,
			                                   &ABaseCharacter::Look);
			// Interaction with world
			EnhancedInputComponent->BindAction(GrabAction, ETriggerEvent::Started, BaseCharacter,
			                                   &ABaseCharacter::Grab);
			EnhancedInputComponent->BindAction(ThrowAction, ETriggerEvent::Started, BaseCharacter,
			                                   &ABaseCharacter::Throw);
			EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this,
			                                   &ABasePlayerController::Interact);
			// Interaction with PinLock
			EnhancedInputComponent->BindAction(MouseClickAction, ETriggerEvent::Started, BaseCharacter,
			                                   &ABaseCharacter::MouseClick);
			// Toggle Flashlight
			EnhancedInputComponent->BindAction(ToggleFlashlightAction, ETriggerEvent::Completed, BaseCharacter,
			                                   &ABaseCharacter::ToggleFlashlight);
		}
	}
}

void ABasePlayerController::Interact()
{
	if (auto* PlayerCharacter = Cast<ABaseCharacter>(GetCharacter()))
	{
		PlayerCharacter->Interact();

		if (const auto& Item = PlayerCharacter->PickUp(); Item.IsSet() && !Inventory->IsFull())
		{
			Inventory->AddItem(Item.GetValue());
		}
	}
}

FText ABasePlayerController::HintMessage() const // TODO: Add Action mapping based Hint construction
{
	if (auto* PlayerCharacter = Cast<ABaseCharacter>(GetCharacter()))
	{
		return PlayerCharacter->HintMessage();
	}
	return FText::GetEmpty();
}

TOptional<FKey> ABasePlayerController::GetKeyByAction(const UInputAction* Action) const
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

TOptional<FKey> ABasePlayerController::GrabKey() const
{
	return GetKeyByAction(GrabAction);
}

TOptional<FKey> ABasePlayerController::ThrowKey() const
{
	return GetKeyByAction(ThrowAction);
}

TOptional<FKey> ABasePlayerController::InteractKey() const
{
	return GetKeyByAction(InteractAction);
}

UInventory* ABasePlayerController::GetInventory() const
{
	return Inventory;
}

FVector ABasePlayerController::GetWorldLocationFromCursor(FVector& WorldDirection) const
{
	FVector WorldLocation;
	DeprojectMousePositionToWorld(WorldLocation, WorldDirection);
	return WorldLocation;
}
