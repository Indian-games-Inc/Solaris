// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetMaxWalkSpeed.h"

#include "AIController.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"

EBTNodeResult::Type UBTTask_SetMaxWalkSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController { OwnerComp.GetAIOwner() };
	
	// AIController->GetCharacter()->GetMovementComponent()->MaxWalkSpeed = MaxWalkSpeed;
	
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

FString UBTTask_SetMaxWalkSpeed::GetStaticDescription() const
{
	return FString::Printf(TEXT("Speed: %f"), MaxWalkSpeed);
}
