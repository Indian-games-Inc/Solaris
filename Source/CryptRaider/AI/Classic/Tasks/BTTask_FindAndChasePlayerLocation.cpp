// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindAndChasePlayerLocation.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"

UBTTask_FindAndChasePlayerLocation::UBTTask_FindAndChasePlayerLocation()
{
	NodeName = TEXT("Find And Chase Player Location");

	BlackboardKey.AddVectorFilter(this,
	                              GET_MEMBER_NAME_CHECKED(UBTTask_FindAndChasePlayerLocation, BlackboardKey)
	);
}

EBTNodeResult::Type UBTTask_FindAndChasePlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp,
                                                                    uint8* NodeMemory)
{
	AAIController* AIController { OwnerComp.GetAIOwner() };
	UBlackboardComponent* BlackboardComponent { OwnerComp.GetBlackboardComponent() };

	if (IsValid(AIController) && IsValid(BlackboardComponent))
	{
		FVector TargetLocation { BlackboardComponent->GetValueAsVector(BlackboardKey.SelectedKeyName) };

		if (const ACharacter* PlayerCharacter = GetWorld()->GetFirstPlayerController()->GetCharacter())
		{
			TargetLocation = PlayerCharacter->GetActorLocation();
		}

		BlackboardComponent->SetValueAsVector(BlackboardKey.SelectedKeyName, TargetLocation);
		AIController->MoveToLocation(TargetLocation);

		return FinishTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	
	return FinishTask(OwnerComp, EBTNodeResult::Failed);
}

FString UBTTask_FindAndChasePlayerLocation::GetStaticDescription() const
{
	return FString::Printf(TEXT("Vector: %s"), *BlackboardKey.SelectedKeyName.ToString());
}
