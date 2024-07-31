// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Base.h"

FString UBTTask_Base::GetStaticDescription() const
{
	UE_LOG(LogTemp, Warning, TEXT("UBTTask_Base::GetStaticDescription called, must be implemented in child classes"));
	return Super::GetStaticDescription();
}

EBTNodeResult::Type UBTTask_Base::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UE_LOG(LogTemp, Warning, TEXT("UBTTask_Base::ExecuteTask called, must be implemented in child classes"));
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

EBTNodeResult::Type UBTTask_Base::FinishTask(UBehaviorTreeComponent& OwnerComp,
                                             const EBTNodeResult::Type ResultType) const
{
	FinishLatentTask(OwnerComp, ResultType);
	return ResultType;
}
