// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Common/Tasks/BTTask_SetIsPursuing.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTTask_SetIsPursuing::UBTTask_SetIsPursuing()
{
	NodeName = "Set Is Pursuing";

	BlackboardKey.AddBoolFilter(
		this,
		GET_MEMBER_NAME_CHECKED(UBTTask_SetIsPursuing, BlackboardKey)
	);
}

FString UBTTask_SetIsPursuing::GetStaticDescription() const
{
	return FString::Printf(TEXT("IsPursuing: %s"), *GetSelectedBlackboardKey().ToString());
}

EBTNodeResult::Type UBTTask_SetIsPursuing::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComponent { OwnerComp.GetBlackboardComponent() };

	BlackboardComponent->SetValueAsBool(GetSelectedBlackboardKey(), Value);

return FinishTask(OwnerComp, EBTNodeResult::Succeeded);
}