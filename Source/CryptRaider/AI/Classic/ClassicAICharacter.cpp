// Fill out your copyright notice in the Description page of Project Settings.


#include "ClassicAICharacter.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "CryptRaider/Player/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AClassicAICharacter::AClassicAICharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("AI Perception");
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AClassicAICharacter::OnTargetPerceptionUpdated);
}

void AClassicAICharacter::TriggerAttack()
{
	if (!GetWorldTimerManager().IsTimerActive(AttackAnimationTimerHandle))
	{
		GetCharacterMovement()->DisableMovement();

		PlayAttackAnimation();
		GetWorld()->GetTimerManager().SetTimer(AttackTraceTimerHandle,
											   this, &AClassicAICharacter::AttackTrace,
											   AttackTraceRate,
											   true);
	}
}

void AClassicAICharacter::PlayAttackAnimation()
{
	if (!GetWorldTimerManager().IsTimerActive(AttackAnimationTimerHandle))
	{
		const float Duration = PlayAnimMontage(AttackAnimation);
		GetWorld()->GetTimerManager().SetTimer(AttackAnimationTimerHandle,
											   this, &AClassicAICharacter::StopAttack,
											   Duration);	
	}
}

void AClassicAICharacter::AttackTrace()
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

void AClassicAICharacter::StopAttack()
{
	StopAttackTrace();
	GetWorld()->GetTimerManager().ClearTimer(AttackAnimationTimerHandle);

	GetCharacterMovement()->SetDefaultMovementMode();
}

void AClassicAICharacter::StopAttackTrace()
{
	GetWorld()->GetTimerManager().ClearTimer(AttackTraceTimerHandle);
}

void AClassicAICharacter::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (const auto* Player = Cast<ABaseCharacter>(Actor); !IsValid(Player))
	{
		UE_LOG(LogTemp, Warning, TEXT("Detected non-player Actor"));
		return;
	}
	
	if (auto* AIController = Cast<AAIController>(GetController()); IsValid(AIController))
	{
		if (auto* BlackboardComponent = AIController->GetBlackboardComponent(); IsValid(BlackboardComponent))
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
}

void AClassicAICharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}
