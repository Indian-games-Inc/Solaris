// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAICharacter.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "CryptRaider/Actor/Destructible/Projectile.h"
#include "CryptRaider/Player/BaseCharacter.h"
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

void ABaseAICharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &ABaseAICharacter::OnHitEvent);
}

void ABaseAICharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}

UBlackboardComponent* ABaseAICharacter::GetBlackboardComponent() const
{
	if (auto* AIController = Cast<AAIController>(GetController()); IsValid(AIController))
	{
		return AIController->GetBlackboardComponent();
	}

	return nullptr;
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

void ABaseAICharacter::HandleStun()
{
	if (!GetWorld()->GetTimerManager().IsTimerActive(StunTimerHandle))
	{
		StartStun();
		const float AnimDuration = PlayAnimMontage(StunAnimation);
		const float TimerDuration = std::max(AnimDuration, StunDuration);

		GetWorld()->GetTimerManager().SetTimer(StunTimerHandle, this, &ABaseAICharacter::FinishStun, TimerDuration);
	}
}

void ABaseAICharacter::StartStun()
{
	GetCharacterMovement()->DisableMovement();
	SetSensesEnabled(false);
	IsStunned = true;

	if (auto* BlackboardComponent = GetBlackboardComponent(); IsValid(BlackboardComponent))
	{
		BlackboardComponent->SetValueAsBool(IsPlayerOnSightName, false);
	}
}

void ABaseAICharacter::FinishStun()
{
	GetCharacterMovement()->SetDefaultMovementMode();
	SetSensesEnabled(true);
	IsStunned = false;

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

void ABaseAICharacter::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (const auto* Player = Cast<ABaseCharacter>(Actor); !IsValid(Player))
	{
		UE_LOG(LogTemp, Warning, TEXT("Detected non-player Actor"));
		return;
	}
	
	if (auto* BlackboardComponent = GetBlackboardComponent(); IsValid(BlackboardComponent))
	{
		if (Stimulus.WasSuccessfullySensed())
		{
			BlackboardComponent->SetValueAsBool(IsPlayerOnSightName, true);
			BlackboardComponent->SetValueAsBool(IsPursuingPlayerName, true);
		}
		else
		{
			BlackboardComponent->SetValueAsBool(IsPlayerOnSightName, false);
		}
	}
}

void ABaseAICharacter::OnHitEvent(UPrimitiveComponent* HitComp,
                                     AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                     FVector NormalImpulse, const FHitResult& Hit)
{
	// Debug purpose only
	// DrawDebugSphere(GetWorld(), Hit.Location, 10, 10, FColor::Cyan, false, 3);
	if (const auto* Projectile = Cast<AProjectile>(OtherActor); IsValid(Projectile) && Projectile->IsCharged())
	{
		HandleStun();

		if (auto* BlackboardComponent = GetBlackboardComponent(); IsValid(BlackboardComponent))
		{
			BlackboardComponent->SetValueAsVector(HitLocationKeyName, Hit.Location);
		}
	}
}
