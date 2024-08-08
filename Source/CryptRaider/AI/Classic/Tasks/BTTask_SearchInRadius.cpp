// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SearchInRadius.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_SearchInRadius::UBTTask_SearchInRadius()
{
	NodeName = "Search In Radius";

	BlackboardKey.AddVectorFilter(
		this,
		GET_MEMBER_NAME_CHECKED(UBTTask_SearchInRadius, BlackboardKey)
	);
}

FString UBTTask_SearchInRadius::GetStaticDescription() const
{
	return FString::Printf(TEXT("TargetLocation: %s\nRadius: %f"), *GetSelectedBlackboardKey().ToString(), SearchRadius);
}

EBTNodeResult::Type UBTTask_SearchInRadius::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComponent { OwnerComp.GetBlackboardComponent() };

	if (IsValid(BlackboardComponent))
	{
		const FVector Origin = BlackboardComponent->GetValueAsVector(GetSelectedBlackboardKey());
		const UNavigationSystemV1* NavigationSystem{ UNavigationSystemV1::GetCurrent(GetWorld()) };

		if (FNavLocation Location {};
			IsValid(NavigationSystem) && NavigationSystem->GetRandomPointInNavigableRadius(Origin, SearchRadius, Location))
		{
			BlackboardComponent->SetValueAsVector(GetSelectedBlackboardKey(), Location.Location);
		}

		return FinishTask(OwnerComp, EBTNodeResult::Succeeded);
	}

	return FinishTask(OwnerComp, EBTNodeResult::Failed);
}


