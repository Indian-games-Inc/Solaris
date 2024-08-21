// Fill out your copyright notice in the Description page of Project Settings.


#include "Movement.h"

#include "IAutomationControllerManager.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values for this component's properties
UMovement::UMovement()
{
	PrimaryComponentTick.bCanEverTick = true;

	CharacterRef = nullptr;
	
	MaxStamina = 100.f;
	MinStamina = 0.f;
	CurrentStamina = 0.f;
	StaminaRestoreThreshold = 50.f;
	SprintSpeed = 600.f;
	WalkSpeed = 400.f;
	SprintStaminaConsumption = 5.f;
	JumpStaminaConsumption = 30.f;
	StaminaConsumptionRate = 0.5f;
	StaminaRestoration = 5.f;
	StaminaRestorationRate = 0.2f;
	StaminaRestorationDelay = 1.f;

	bIsOnLadder = false;
}

// Called when the game starts
void UMovement::BeginPlay()
{
	Super::BeginPlay();
	CurrentStamina = MaxStamina;
	CharacterRef = Cast<ACharacter>(GetOwner());

	SetMaxWalkSpeed(WalkSpeed);
}

void UMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!GetTimerManager().IsTimerActive(StaminaRestorationTimerHandle)
		&& CurrentStamina < MaxStamina)
	{
		StartStaminaRestoration();
	}
}

float UMovement::GetStaminaPercent() const
{
	return CurrentStamina / MaxStamina;
}

void UMovement::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	const FVector Forward = CharacterRef->GetActorForwardVector();
	const FVector Right = CharacterRef->GetActorRightVector();
	const FVector Up = CharacterRef->GetActorUpVector();

	if (!bIsOnLadder)
	{
		CharacterRef->AddMovementInput(Forward, MovementVector.Y);
		CharacterRef->AddMovementInput(Right, MovementVector.X);
	}
	else
	{
		CharacterRef->AddMovementInput(Up, MovementVector.Y);
		CharacterRef->AddMovementInput(Forward, MovementVector.Y);
	}

	GetOwner()->MakeNoise(MoveLoudness, GetOwner()->GetInstigator(), GetOwner()->GetActorLocation());
}

void UMovement::Jump()
{
	if (!bIsStaminaBlocked && JumpStaminaConsumption <= CurrentStamina)
	{
		ConsumeStamina(JumpStaminaConsumption);

		CharacterRef->UnCrouch();
		CharacterRef->Jump();
		GetOwner()->MakeNoise(JumpLoudness, GetOwner()->GetInstigator(), GetOwner()->GetActorLocation());
	}
}

void UMovement::Crouch()
{
	if (CharacterRef->bIsCrouched)
	{
		CharacterRef->UnCrouch();
	}
	else
	{
		CharacterRef->Crouch();
	}
}

void UMovement::StartSprint()
{
	if (CurrentStamina > MinStamina)
	{
		CharacterRef->UnCrouch();
		SetMaxWalkSpeed(SprintSpeed);
		GetTimerManager().SetTimer(SprintUpdateTimerHandle,
		                           this, &UMovement::SprintTick,
		                           StaminaConsumptionRate, true);
	}
}

void UMovement::StopSprint()
{
	GetTimerManager().ClearTimer(SprintUpdateTimerHandle);

	SetMaxWalkSpeed(WalkSpeed);
}

void UMovement::SetOnLadder(const bool IsOnLadder)
{
	bIsOnLadder = IsOnLadder;

	auto* CharacterMovement = CharacterRef->GetCharacterMovement();
	if (bIsOnLadder)
	{
		CharacterMovement->SetMovementMode(MOVE_Flying);	
	} else
	{
		CharacterMovement->SetMovementMode(MOVE_Walking);
	}
}

void UMovement::SprintTick()
{
	if (IsConsumingStamina())
	{
		ConsumeStamina(SprintStaminaConsumption);
		GetOwner()->MakeNoise(SprintLoudness, GetOwner()->GetInstigator(), GetOwner()->GetActorLocation());
	}
	if (CurrentStamina <= MinStamina)
	{
		bIsStaminaBlocked = true;
		StopSprint();
	}
}

void UMovement::StaminaRestorationTick()
{
	RestoreStamina(StaminaRestoration);

	if (CurrentStamina >= StaminaRestoreThreshold)
	{
		bIsStaminaBlocked = false;
	}

	if (CurrentStamina >= MaxStamina)
	{
		StopStaminaRestoration();
	}
}

void UMovement::StartStaminaRestoration()
{
	GetTimerManager().SetTimer(StaminaRestorationTimerHandle,
							   this, &UMovement::StaminaRestorationTick,
							   StaminaConsumptionRate, true,
							   StaminaRestorationDelay);
}

void UMovement::StopStaminaRestoration()
{
	GetTimerManager().ClearTimer(StaminaRestorationTimerHandle);
}

FTimerManager& UMovement::GetTimerManager() const
{
	return GetWorld()->GetTimerManager();
}

void UMovement::SetMaxWalkSpeed(const float Speed) const
{
	if (IsValid(CharacterRef))
	{
		CharacterRef->GetCharacterMovement()->MaxWalkSpeed = Speed;
	}
}

bool UMovement::IsConsumingStamina() const
{
	const auto* CharacterMovement = CharacterRef->GetCharacterMovement();

	const bool IsFlying = CharacterMovement->IsFlying();
	const bool IsFalling = CharacterMovement->IsFalling();
	const bool IsStanding = CharacterMovement->Velocity.Length() == 0;

	return !bIsStaminaBlocked && !(IsFlying || IsFalling || IsStanding);
}

void UMovement::ConsumeStamina(const float Amount)
{
	StopStaminaRestoration();
	CurrentStamina = FMath::Clamp(CurrentStamina - Amount,
									  MinStamina,
									  MaxStamina);
}

void UMovement::RestoreStamina(const float Amount)
{
	CurrentStamina = FMath::Clamp(CurrentStamina + Amount,
									  MinStamina,
									  MaxStamina);
}
