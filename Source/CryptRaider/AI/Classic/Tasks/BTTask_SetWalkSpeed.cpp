// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetWalkSpeed.h"

#include "AIController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTTask_SetWalkSpeed::UBTTask_SetWalkSpeed()
{
	NodeName = "Set Walk Speed";
}

EBTNodeResult::Type UBTTask_SetWalkSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController { OwnerComp.GetAIOwner() };
	
	AIController->GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
	
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

FString UBTTask_SetWalkSpeed::GetStaticDescription() const
{
	return FString::Printf(TEXT("Speed: %f"), MaxWalkSpeed);
}
