// Fill out your copyright notice in the Description page of Project Settings.


#include "Movement.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values for this component's properties
UMovement::UMovement()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	CharacterRef = nullptr;
	
	MaxStamina = 100.f;
	MinStamina = 0.f;
	CurrentStamina = 0.f;
	StaminaRestoreThreshold = 50.f;
	SprintSpeed = 600.f;
	WalkSpeed = 400.f;
	StaminaConsumption = 5.f;
	StaminaConsumptionRate = 0.5f;
	StaminaRestoration = 5.f;
	StaminaRestorationRate = 0.2f;
}

// Called when the game starts
void UMovement::BeginPlay()
{
	Super::BeginPlay();
	CurrentStamina = MaxStamina;
	CharacterRef = Cast<ACharacter>(GetOwner());

	SetMaxWalkSpeed(WalkSpeed);
}

// Called every frame
void UMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

float UMovement::GetStaminaPercent() const
{
	return CurrentStamina / MaxStamina;
}

void UMovement::StartSprint()
{
	if (!bUseThreshold)
	{
		GetTimerManager().ClearTimer(StaminaRestorationTimerHandle);

		if (CurrentStamina > MinStamina)
		{
			SetMaxWalkSpeed(SprintSpeed);
			GetTimerManager().SetTimer(SprintUpdateTimerHandle,
			                           this, &UMovement::SprintTick,
			                           StaminaConsumptionRate, true);
		}
	}
}

void UMovement::SprintTick()
{
	CurrentStamina = FMath::Clamp(CurrentStamina - StaminaConsumption,
	                              MinStamina,
	                              MaxStamina);

	if (CurrentStamina <= MinStamina)
	{
		bUseThreshold = true;
		StopSprint();
	}
}

void UMovement::StopSprint()
{
	GetTimerManager().ClearTimer(SprintUpdateTimerHandle);

	SetMaxWalkSpeed(WalkSpeed);

	GetTimerManager().SetTimer(StaminaRestorationTimerHandle,
	                           this, &UMovement::StaminaRestorationTick,
	                           StaminaConsumptionRate, true);
}

void UMovement::StaminaRestorationTick()
{
	CurrentStamina = FMath::Clamp(CurrentStamina + StaminaConsumption,
	                              MinStamina,
	                              MaxStamina);

	if (CurrentStamina >= StaminaRestoreThreshold)
	{
		bUseThreshold = false;
	}

	if (CurrentStamina >= MaxStamina)
	{
		StopStaminaRestoration();
	}
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
