// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "BaseCharacter.h"
#include "CryptRaider/Component/Inventory.h"
#include "CryptRaider/Data/InventoryItemWrapper.h"

ABasePlayerController::ABasePlayerController()
{
	Inventory = CreateDefaultSubobject<UInventory>(TEXT("Inventory"));
}

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
	ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this,
		                                   &ABasePlayerController::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this,
		                                   &ABasePlayerController::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this,
		                                   &ABasePlayerController::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this,
		                                   &ABasePlayerController::Look);

		// Crouching
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this,
		                                   &ABasePlayerController::OnCrouch);

		// Interaction with world
		EnhancedInputComponent->BindAction(GrabAction, ETriggerEvent::Started, this,
		                                   &ABasePlayerController::Grab);
		EnhancedInputComponent->BindAction(ThrowAction, ETriggerEvent::Started, this,
		                                   &ABasePlayerController::Throw);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this,
		                                   &ABasePlayerController::Interact);
	}
}

void ABasePlayerController::Move(const FInputActionValue& Value)
{
	if (auto* PlayerCharacter = Cast<ABaseCharacter>(GetCharacter()))
	{
		PlayerCharacter->Move(Value);
	}
}

void ABasePlayerController::Look(const FInputActionValue& Value)
{
	if (auto* PlayerCharacter = Cast<ABaseCharacter>(GetCharacter()))
	{
		PlayerCharacter->Look(Value);
	}
}

void ABasePlayerController::Jump()
{
	if (auto* PlayerCharacter = Cast<ABaseCharacter>(GetCharacter()))
	{
		PlayerCharacter->Jump();
	}
}

void ABasePlayerController::StopJumping()
{
	if (auto* PlayerCharacter = Cast<ABaseCharacter>(GetCharacter()))
	{
		PlayerCharacter->StopJumping();
	}
}

void ABasePlayerController::OnCrouch()
{
	if (auto* PlayerCharacter = Cast<ABaseCharacter>(GetCharacter()))
	{
		PlayerCharacter->OnCrouch();
	}
}

void ABasePlayerController::Grab()
{
	if (auto* PlayerCharacter = Cast<ABaseCharacter>(GetCharacter()))
	{
		PlayerCharacter->Grab();
	}
}

void ABasePlayerController::Throw()
{
	if (auto* PlayerCharacter = Cast<ABaseCharacter>(GetCharacter()))
	{
		PlayerCharacter->Throw();
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
