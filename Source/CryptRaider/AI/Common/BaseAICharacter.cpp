// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAICharacter.h"

#include "CryptRaider/Damage/Event/StunDamageEvent.h"
#include "CryptRaider/Player/BaseCharacter.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AISenseConfig.h"

// Sets default values
ABaseAICharacter::ABaseAICharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("AI Perception");
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ABaseAICharacter::OnTargetPerceptionUpdated);
}

void ABaseAICharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}

void ABaseAICharacter::TriggerAttack()
{
	if (!GetWorldTimerManager().IsTimerActive(AttackAnimationTimerHandle))
	{
		GetCharacterMovement()->DisableMovement();

		PlayAttackAnimation();
		GetWorld()->GetTimerManager().SetTimer(AttackTraceTimerHandle,
		                                       this, &ABaseAICharacter::AttackTrace,
		                                       AttackTraceRate,
		                                       true);
	}
}

void ABaseAICharacter::PlayAttackAnimation()
{
	if (!GetWorldTimerManager().IsTimerActive(AttackAnimationTimerHandle))
	{
		const float Duration = PlayAnimMontage(AttackAnimation);
		GetWorld()->GetTimerManager().SetTimer(AttackAnimationTimerHandle,
		                                       this, &ABaseAICharacter::StopAttack,
		                                       Duration);
	}
}

void ABaseAICharacter::AttackTrace()
{
	const FVector Start = GetMesh()->GetSocketLocation(AttackStartSocketName);
	const FVector End = GetMesh()->GetSocketLocation(AttackEndSocketName);

	float Radius = 10.f;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(Radius);

	// For debug purpose
	// DrawDebugCylinder(GetWorld(), Start, End, Radius, 10, FColor::Cyan, false, 0.1);

	FHitResult HitResult;
	if (GetWorld()->SweepSingleByChannel(HitResult, Start, End, FQuat::Identity, ECC_Camera, Sphere))
	{
		if (auto* PlayerCharacter = Cast<ABaseCharacter>(HitResult.GetActor()); IsValid(PlayerCharacter))
		{
			UGameplayStatics::ApplyDamage(PlayerCharacter,
			                              AttackDamage,
			                              GetController(), this,
			                              UDamageType::StaticClass());
			StopAttackTrace();
		}
	}
}

void ABaseAICharacter::StopAttack()
{
	StopAttackTrace();
	GetWorld()->GetTimerManager().ClearTimer(AttackAnimationTimerHandle);

	GetCharacterMovement()->SetDefaultMovementMode();
}

void ABaseAICharacter::StopAttackTrace()
{
	GetWorld()->GetTimerManager().ClearTimer(AttackTraceTimerHandle);
}

void ABaseAICharacter::GetStunned(const float& Duration)
{
	if (bIsStunResistant)
	{
		return;
	}
	
	if (!GetWorld()->GetTimerManager().IsTimerActive(StunTimerHandle))
	{
		if (IsValid(StunAnimation))
		{
			StartStun();

			const float PlayRate = StunAnimation->GetPlayLength() / Duration > 0 ? Duration : 1.f;
			const float AnimDuration = PlayAnimMontage(StunAnimation, PlayRate);

			GetWorld()->GetTimerManager().SetTimer(StunTimerHandle, this, &ABaseAICharacter::FinishStun, AnimDuration);
		}
	}
}

bool ABaseAICharacter::IsStunResistant()
{
	return bIsStunResistant;
}

void ABaseAICharacter::StartStun()
{
	GetCharacterMovement()->DisableMovement();
	SetSensesEnabled(false);
	bIsStunned = true;

	const FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetCharacter()->GetActorLocation();

	OnPlayerOnSightUpdate.Broadcast(false, PlayerLocation);
}

void ABaseAICharacter::FinishStun()
{
	GetCharacterMovement()->SetDefaultMovementMode();
	SetSensesEnabled(true);
	bIsStunned = false;

	GetWorld()->GetTimerManager().ClearTimer(StunTimerHandle);
}

void ABaseAICharacter::SetSensesEnabled(const bool IsEnabled)
{
	for (auto Iter = AIPerceptionComponent->GetSensesConfigIterator(); Iter; ++Iter)
	{
		const UAISenseConfig* SenseConfig = *Iter;
		AIPerceptionComponent->SetSenseEnabled(SenseConfig->GetSenseImplementation(), IsEnabled);
	}

	AIPerceptionComponent->ForgetAll();
}

float ABaseAICharacter::TakeDamage(float Damage, const FDamageEvent& DamageEvent,
                                   AController* EventInstigator, AActor* DamageCauser)
{
	if (DamageEvent.IsOfType(FStunDamageEvent::ClassID))
	{
		const auto* StunDamageEvent = static_cast<const FStunDamageEvent*>(&DamageEvent);
		const UDamageType* DamageTypeCDO = DamageEvent.DamageTypeClass ? DamageEvent.DamageTypeClass->GetDefaultObject<UDamageType>() : GetDefault<UDamageType>();
		
		OnTakeStunDamage.Broadcast(this,
		                           Damage,
		                           StunDamageEvent->HitInfo,
		                           EventInstigator,
		                           DamageTypeCDO,
		                           DamageCauser);

		GetStunned(StunDamageEvent->StunDuration);
	}

	return Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
}

void ABaseAICharacter::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (const auto* Player = Cast<ABaseCharacter>(Actor); !IsValid(Player))
	{
		UE_LOG(LogTemp, Warning, TEXT("Detected non-player Actor"));
		return;
	}

	OnPlayerOnSightUpdate.Broadcast(Stimulus.WasSuccessfullySensed(), Stimulus.StimulusLocation);
}
