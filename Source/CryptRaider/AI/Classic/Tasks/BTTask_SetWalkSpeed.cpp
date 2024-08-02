// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetWalkSpeed.h"

#include "AIController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTTask_SetWalkSpeed::UBTTask_SetWalkSpeed()
{
	NodeName = "Set Walk Speed";
}

FString UBTTask_SetWalkSpeed::GetStaticDescription() const
{
	return FString::Printf(TEXT("Speed: %f"), MaxWalkSpeed);
}

EBTNodeResult::Type UBTTask_SetWalkSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (const AAIController* AIController { OwnerComp.GetAIOwner() }; IsValid(AIController))
	{
		AIController->GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
	
		return FinishTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	
	return FinishTask(OwnerComp, EBTNodeResult::Failed);
}