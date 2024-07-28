// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_LastPlayerLocation.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "CryptRaider/Player/BaseCharacter.h"

UBTTask_LastPlayerLocation::UBTTask_LastPlayerLocation()
{
	NodeName = "Last Player Location";

	BlackboardKey.AddVectorFilter(this,
							  GET_MEMBER_NAME_CHECKED(UBTTask_LastPlayerLocation, BlackboardKey)
);
}

EBTNodeResult::Type UBTTask_LastPlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController { OwnerComp.GetAIOwner() };

	if (const auto PlayerCharacter = Cast<ABaseCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter()))
	{
		AIController->GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, PlayerCharacter->GetActorLocation());

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	return EBTNodeResult::Failed;
}

FString UBTTask_LastPlayerLocation::GetStaticDescription() const
{
	return FString::Printf(TEXT("TargetLocation: %s"), *BlackboardKey.SelectedKeyName.ToString());
}
