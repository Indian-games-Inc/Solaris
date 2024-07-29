// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SearchInRadius.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_SearchInRadius::UBTTask_SearchInRadius()
{
	NodeName = "Search In Radius";

	BlackboardKey.AddVectorFilter(this,
	                              GET_MEMBER_NAME_CHECKED(UBTTask_SearchInRadius, BlackboardKey)
	);
}

FString UBTTask_SearchInRadius::GetStaticDescription() const
{
	return FString::Printf(TEXT("TargetLocation: %s, Radius: %f"), *BlackboardKey.SelectedKeyName.ToString(), SearchRadius);
}

EBTNodeResult::Type UBTTask_SearchInRadius::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController { OwnerComp.GetAIOwner() };
	UBlackboardComponent* BlackboardComponent = AIController->GetBlackboardComponent();

	const FVector Origin = BlackboardComponent->GetValueAsVector(BlackboardKey.SelectedKeyName);
	const UNavigationSystemV1* NavigationSystem{ UNavigationSystemV1::GetCurrent(GetWorld()) };

	if (FNavLocation Location {};
		IsValid(NavigationSystem) && NavigationSystem->GetRandomPointInNavigableRadius(Origin, SearchRadius, Location))
	{
		BlackboardComponent->SetValueAsVector(BlackboardKey.SelectedKeyName, Location.Location);
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}


