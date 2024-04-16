// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

#include "BaseCharacter.h"

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetupInputComponent();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	ABaseCharacter* PlayerCharacter = Cast<ABaseCharacter>(GetPawn());
	
	if (!PlayerCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to Cast Player Character"));
		return;
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, PlayerCharacter, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, PlayerCharacter, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, PlayerCharacter, &ABaseCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, PlayerCharacter, &ABaseCharacter::Look);

		// Crouching
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, PlayerCharacter, &ABaseCharacter::OnCrouch);

		// Interaction with world
		EnhancedInputComponent->BindAction(GrabAction, ETriggerEvent::Started, PlayerCharacter, &ABaseCharacter::Grab);
		EnhancedInputComponent->BindAction(ThrowAction, ETriggerEvent::Started, PlayerCharacter, &ABaseCharacter::Throw);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, PlayerCharacter, &ABaseCharacter::Interact);
	}
}
