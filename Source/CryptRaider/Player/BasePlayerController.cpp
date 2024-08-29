// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "BaseCharacter.h"
#include "CryptRaider/Component/Flashlight.h"
#include "CryptRaider/Component/Grabber.h"
#include "CryptRaider/Component/Interactor.h"
#include "CryptRaider/Component/Inventory.h"
#include "CryptRaider/Component/Picker.h"


ABasePlayerController::ABasePlayerController()
{
	Inventory = CreateDefaultSubobject<UInventory>(TEXT("Inventory"));
}

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetupInput();

	if (auto* Picker = GetCharacter()->FindComponentByClass<UPicker>(); IsValid(Picker))
	{
		Picker->OnItemPicked.AddUniqueDynamic(this, &ABasePlayerController::OnItemPicked);
	}
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
			//Movement
			if (auto* Movement = BaseCharacter->FindComponentByClass<UMovement>(); IsValid(Movement))
			{
				// Jump
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
			// Grabber
			if (auto* Grabber = BaseCharacter->FindComponentByClass<UGrabber>(); IsValid(Grabber))
			{
				EnhancedInputComponent->BindAction(GrabAction, ETriggerEvent::Started, Grabber,
				                                   &UGrabber::Interact);
				EnhancedInputComponent->BindAction(ThrowAction, ETriggerEvent::Started, Grabber,
				                                   &UGrabber::Throw);
			}

			// Interaction
			if (auto* Interactor = BaseCharacter->FindComponentByClass<UInteractor>(); IsValid(Interactor))
			{
				EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, Interactor,
				                                   &UInteractor::Interact);
			}

			if (auto* Picker = BaseCharacter->FindComponentByClass<UPicker>(); IsValid(Picker))
			{
				EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, Picker,
												   &UPicker::Interact);
			}

			// Interaction with PinLock
			EnhancedInputComponent->BindAction(MouseClickAction, ETriggerEvent::Started, BaseCharacter,
			                                   &ABaseCharacter::MouseClick);
			// Toggle Flashlight
			if (const auto* FlashlightComponent = BaseCharacter->FindComponentByClass<UChildActorComponent>();
				IsValid(FlashlightComponent))
			{
				if (auto* Flashlight = Cast<AFlashlight>(FlashlightComponent->GetChildActor()))
				{
					EnhancedInputComponent->BindAction(ToggleFlashlightAction, ETriggerEvent::Completed, Flashlight,
					                                   &AFlashlight::Toggle);
				}
			}
		}
	}
}

void ABasePlayerController::OnItemPicked(const FInventoryItemWrapper& Item)
{
	Inventory->AddItem(Item);
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
