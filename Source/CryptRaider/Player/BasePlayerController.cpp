// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "BaseCharacter.h"
#include "CryptRaider/Actor/Door/DoorPinLock.h"
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

void ABasePlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
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
		// Interaction with PinLock
		EnhancedInputComponent->BindAction(MouseClickAction, ETriggerEvent::Started, this,
								   &ABasePlayerController::MouseClick);
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
		PlayerCharacter->Look(Value, PinLock);
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

/** Pin code part **/
void ABasePlayerController::SetPinLock(ADoorPinLock* PinLockRef)
{
	PinLock = PinLockRef;
	this->SetIgnoreMoveInput(PinLock != nullptr);
	const auto PlayerController = Cast<ABasePlayerController>(this);
	if (PinLock)
	{
		//switch camera to pin lock
		PlayerController->SetViewTargetWithBlend(PinLock, 0.1);
	}
	else
	{
		//switch camera to player
		SetViewTargetWithBlend(GetCharacter());
	}
}

bool ABasePlayerController::IsInPinLock() const
{
	return PinLock ? true : false;
}

void ABasePlayerController::MouseClick()
{
	if (PinLock)
	{
		FVector WorldDirection;
		FVector Start = GetWorldLocationFromCursor(WorldDirection);
		FVector End = Start + WorldDirection * 70;

		if (auto* PlayerCharacter = Cast<ABaseCharacter>(GetCharacter()))
		{
			PlayerCharacter->InteractWithPinLock(Start, End, PinLock);
		}
	}
}

FVector ABasePlayerController::GetWorldLocationFromCursor(FVector& WorldDirection) const
{
	FVector WorldLocation;
	DeprojectMousePositionToWorld(WorldLocation, WorldDirection);
	return WorldLocation;
}
