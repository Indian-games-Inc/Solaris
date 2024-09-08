// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_GetStunned.h"

#include "AIController.h"
#include "CryptRaider/AI/Common/BaseAICharacter.h"

class ABaseAICharacter;

UBTTask_GetStunned::UBTTask_GetStunned()
{
	NodeName = "Get Stunned";
	StunDuration = 0.f;
}

FString UBTTask_GetStunned::GetStaticDescription() const
{
	return Super::GetStaticDescription();
}

EBTNodeResult::Type UBTTask_GetStunned::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController { OwnerComp.GetAIOwner() };

	if (ABaseAICharacter* AICharacter = Cast<ABaseAICharacter>(AIController->GetCharacter());
		IsValid(AICharacter))
	{
		AICharacter->GetStunned(StunDuration);

		return FinishTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	return FinishTask(OwnerComp, EBTNodeResult::Failed);
}
