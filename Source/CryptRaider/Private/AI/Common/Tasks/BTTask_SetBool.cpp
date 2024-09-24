// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Common/Tasks/BTTask_SetBool.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetStringLibrary.h"

UBTTask_SetBool::UBTTask_SetBool()
{
	NodeName = "Set Bool";
	Value = false;
}

FString UBTTask_SetBool::GetStaticDescription() const
{
	return FString::Printf(TEXT("Key: %s, Value: %s"),
						   *GetSelectedBlackboardKey().ToString(),
						   *UKismetStringLibrary::Conv_BoolToString(Value));
}

EBTNodeResult::Type UBTTask_SetBool::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComponent { OwnerComp.GetBlackboardComponent() };
	BlackboardComponent->SetValueAsBool(GetSelectedBlackboardKey(), Value);

	return FinishTask(OwnerComp, EBTNodeResult::Succeeded);
}
