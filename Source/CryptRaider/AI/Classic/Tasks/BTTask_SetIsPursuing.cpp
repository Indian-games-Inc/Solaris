// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetIsPursuing.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_SetIsPursuing::UBTTask_SetIsPursuing()
{
	NodeName = "Set Is Pursuing";

	BlackboardKey.AddBoolFilter(this,
							  GET_MEMBER_NAME_CHECKED(UBTTask_SetIsPursuing, BlackboardKey));
}

EBTNodeResult::Type UBTTask_SetIsPursuing::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController { OwnerComp.GetAIOwner() };

	AIController->GetBlackboardComponent()->SetValueAsBool(BlackboardKey.SelectedKeyName, Value);

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

FString UBTTask_SetIsPursuing::GetStaticDescription() const
{
	return FString::Printf(TEXT("IsPursuing: %s"), *BlackboardKey.SelectedKeyName.ToString());
}
