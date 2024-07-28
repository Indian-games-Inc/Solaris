// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SearchForPlayer.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_SearchForPlayer::UBTTask_SearchForPlayer()
{
	NodeName = TEXT("SearchForPlayer");

	BlackboardKey.AddVectorFilter(this,
	                              GET_MEMBER_NAME_CHECKED(UBTTask_SearchForPlayer, BlackboardKey)
	);
}

EBTNodeResult::Type UBTTask_SearchForPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController { OwnerComp.GetAIOwner() };
	const APawn* Pawn { AIController->GetPawn() };

	const FVector Origin = Pawn->GetActorLocation();

	const UNavigationSystemV1* NavigationSystem{ UNavigationSystemV1::GetCurrent(GetWorld()) };

	if (FNavLocation Location {};
		IsValid(NavigationSystem) && NavigationSystem->GetRandomPointInNavigableRadius(Origin, SearchRadius, Location))
	{
		AIController->GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, Location.Location);
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

FString UBTTask_SearchForPlayer::GetStaticDescription() const
{
	return FString::Printf(TEXT("TargetLocation: %s"), *BlackboardKey.SelectedKeyName.ToString());
}
