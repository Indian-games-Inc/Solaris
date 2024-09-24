// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Common/Tasks/BTTask_AttackPlayer.h"

#include "AIController.h"
#include "AI/Common/BaseAICharacter.h"

UBTTask_AttackPlayer::UBTTask_AttackPlayer()
{
	NodeName = "Attack Player";
}

FString UBTTask_AttackPlayer::GetStaticDescription() const
{
	return FString::Printf(TEXT("Distance: %f"), AttackDistance);
}

EBTNodeResult::Type UBTTask_AttackPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController { OwnerComp.GetAIOwner() };

	if (ABaseAICharacter* AICharacter = Cast<ABaseAICharacter>(AIController->GetCharacter());
		IsValid(AICharacter))
	{
		if (const ACharacter* PlayerCharacter = GetWorld()->GetFirstPlayerController()->GetCharacter())
		{
			const FVector AILocation = AICharacter->GetActorLocation();
			const FVector PlayerLocation = PlayerCharacter->GetActorLocation();

			if (FVector::Distance(AILocation, PlayerLocation) <= AttackDistance)
			{
				AICharacter->TriggerAttack();
			}
		}
	}
	return FinishTask(OwnerComp, EBTNodeResult::Succeeded);
}
