#include "Player/BasePlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Components/WidgetInteractionComponent.h"

#include "Player/BaseCharacter.h"
#include "Player/Components/Flashlight.h"
#include "Player/Components/Grabber.h"
#include "Player/Components/Interactor.h"
#include "Player/Components/Inventory.h"
#include "Player/Components/Picker.h"


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
		if (IsValid(GetCharacter()))
		{
			BindLook(EnhancedInputComponent);
			BindMovement(EnhancedInputComponent);
			BindInteraction(EnhancedInputComponent);
			BindFlashlight(EnhancedInputComponent);
			BindWidgetInteraction(EnhancedInputComponent);
			BindPinLock(EnhancedInputComponent);
		}
	}
}

void ABasePlayerController::BindLook(UEnhancedInputComponent* EnhancedInputComponent) const
{
	if (auto* BaseCharacter = Cast<ABaseCharacter>(GetCharacter()); IsValid(BaseCharacter))
	{
		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, BaseCharacter,
										   &ABaseCharacter::Look);
	}
}

void ABasePlayerController::BindMovement(UEnhancedInputComponent* EnhancedInputComponent) const
{
	//Movement
	if (auto* Movement = GetCharacter()->FindComponentByClass<UMovement>(); IsValid(Movement))
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
}

void ABasePlayerController::BindInteraction(UEnhancedInputComponent* EnhancedInputComponent) const
{
	// Grabber
	if (auto* Grabber = GetCharacter()->FindComponentByClass<UGrabber>(); IsValid(Grabber))
	{
		EnhancedInputComponent->BindAction(GrabAction, ETriggerEvent::Started, Grabber,
										   &UGrabber::Interact);
		EnhancedInputComponent->BindAction(ThrowAction, ETriggerEvent::Started, Grabber,
										   &UGrabber::Throw);
	}

	// Interaction
	if (auto* Interactor = GetCharacter()->FindComponentByClass<UInteractor>(); IsValid(Interactor))
	{
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, Interactor,
										   &UInteractor::Interact);
	}

	// Picker
	if (auto* Picker = GetCharacter()->FindComponentByClass<UPicker>(); IsValid(Picker))
	{
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, Picker,
										   &UPicker::Interact);
	}
}

void ABasePlayerController::BindFlashlight(UEnhancedInputComponent* EnhancedInputComponent) const
{
	if (const auto* FlashlightComponent = GetCharacter()->FindComponentByClass<UChildActorComponent>();
		IsValid(FlashlightComponent))
	{
		if (auto* Flashlight = Cast<AFlashlight>(FlashlightComponent->GetChildActor()))
		{
			EnhancedInputComponent->BindAction(ToggleFlashlightAction, ETriggerEvent::Completed, Flashlight,
											   &AFlashlight::Toggle);
		}
	}
}

void ABasePlayerController::BindWidgetInteraction(UEnhancedInputComponent* EnhancedInputComponent) const
{
	if (auto* WidgetInteractionComponent = GetCharacter()->FindComponentByClass<UWidgetInteractionComponent>();
		IsValid(WidgetInteractionComponent))
	{
		EnhancedInputComponent->BindActionInstanceLambda(
			MouseClickAction, ETriggerEvent::Started,
			[this, WidgetInteractionComponent](const FInputActionInstance& Instance)
			{
				if (const auto& Key = GetKeyByAction(Instance.GetSourceAction()); Key.IsSet())
				{
					WidgetInteractionComponent->PressPointerKey(Key.GetValue());
				}
			});

		EnhancedInputComponent->BindActionInstanceLambda(
			MouseClickAction, ETriggerEvent::Completed,
			[this, WidgetInteractionComponent](const FInputActionInstance& Instance)
			{
				if (const auto& Key = GetKeyByAction(Instance.GetSourceAction()); Key.IsSet())
				{
					WidgetInteractionComponent->ReleasePointerKey(Key.GetValue());
				}
			});
	}
}

void ABasePlayerController::BindPinLock(UEnhancedInputComponent* EnhancedInputComponent) const
{
	if (auto* BaseCharacter = Cast<ABaseCharacter>(GetCharacter()); IsValid(BaseCharacter))
	{
		// Interaction with PinLock
		EnhancedInputComponent->BindAction(MouseClickAction, ETriggerEvent::Started, BaseCharacter,
										   &ABaseCharacter::MouseClick);
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
