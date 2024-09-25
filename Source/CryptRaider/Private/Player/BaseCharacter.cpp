#include "Player/BaseCharacter.h"

#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/DamageEvents.h"

#include "Player/BasePlayerController.h"
#include "Actor/Door/DoorPinLock.h"
#include "Player/Components/Hand.h"
#include "Player/Components/Grabber.h"
#include "Player/Components/Picker.h"
#include "Player/Components/Interactor.h"
#include "GameMode/DefaultGameMode.h"
#include "Player/Components/Flashlight.h"
#include "Player/Components/HintProducer.h"
#include "Damage/Event/StunDamageEvent.h"


ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(RootComponent);
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	FlashlightArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Fashlight Arm"));
	FlashlightArm->SetupAttachment(FirstPersonCameraComponent);
	FlashlightArm->SetRelativeLocation(FVector(0, 0.f, -30.f));

	Flashlight = CreateDefaultSubobject<UChildActorComponent>(TEXT("Flashlight"));
	Flashlight->SetupAttachment(FlashlightArm);
	Flashlight->SetChildActorClass(FlashlightClass);
	
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	SkeletalMeshComponent->SetupAttachment(FirstPersonCameraComponent);

	Hand = CreateDefaultSubobject<UHand>(TEXT("Hand"));
	Hand->SetupAttachment(FirstPersonCameraComponent);

	Grabber = CreateDefaultSubobject<UGrabber>(TEXT("Grabber"));

	Picker = CreateDefaultSubobject<UPicker>(TEXT("Picker"));

	Interactor = CreateDefaultSubobject<UInteractor>(TEXT("Interactor"));

	HintProducer = CreateDefaultSubobject<UHintProducer>(TEXT("Hint Producer"));

	Movement = CreateDefaultSubobject<UMovement>(TEXT("Movement"));
	Health = CreateDefaultSubobject<UHealth>(TEXT("Health"));
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

float ABaseCharacter::TakeDamage(float Damage,
                                 const FDamageEvent& DamageEvent,
                                 AController* EventInstigator,
                                 AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (DamageEvent.IsOfType(FStunDamageEvent::ClassID))
	{
		// TODO Add stun handling
		return DamageToApply;
	}
	
	Health->TakeDamage(DamageToApply);

	if (Health->IsDead())
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


void ABaseCharacter::InteractWithPinLock(FVector& Start, FVector& End)
{
	if (TOptional<FHitResult> HitResult = Hand->GetInteractableWithCoords(Start, End); HitResult.IsSet())
	{
		auto Hit = HitResult.GetValue();
		UE_LOG(LogTemp, Warning, TEXT("B: %s"), *Hit.BoneName.ToString());
		PinLock->PressButton(Hit.BoneName.ToString());
	}
}

/** Pin code part **/
void ABaseCharacter::SetPinLock(TSoftObjectPtr<ADoorPinLock> PinLockRef)
{
	PinLock = PinLockRef;
	const auto PlayerController = Cast<ABasePlayerController>(GetController());
	PlayerController->SetIgnoreMoveInput(PinLock != nullptr);
	if (PinLock)
	{
		//switch camera to pin lock
		PlayerController->SetViewTargetWithBlend(PinLock.Get(), 0.1);
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
