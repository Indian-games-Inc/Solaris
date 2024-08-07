// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetTargetLocation.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTTask_SetTargetLocation::UBTTask_SetTargetLocation()
{
	NodeName = "SetTargetLocation";

	BlackboardKey.AddVectorFilter(
		this,
		GET_MEMBER_NAME_CHECKED(UBTTask_SetTargetLocation, BlackboardKey)
	);
}

FString UBTTask_SetTargetLocation::GetStaticDescription() const
{
	return FString::Printf(TEXT("Target: %s\nLocation: %s"),
	                       *GetSelectedBlackboardKey().ToString(),
	                       *Location.SelectedKeyName.ToString());
}

EBTNodeResult::Type UBTTask_SetTargetLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (UBlackboardComponent* BlackboardComponent { OwnerComp.GetBlackboardComponent() }; IsValid(BlackboardComponent))
	{
		const FVector LocationValue = BlackboardComponent->GetValueAsVector(Location.SelectedKeyName);
		BlackboardComponent->SetValueAsVector(GetSelectedBlackboardKey(), LocationValue);

		return FinishTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	
	return FinishTask(OwnerComp, EBTNodeResult::Failed);
}
