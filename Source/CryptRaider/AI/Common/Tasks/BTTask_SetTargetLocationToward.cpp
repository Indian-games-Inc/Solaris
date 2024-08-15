// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetTargetLocationToward.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"

UBTTask_SetTargetLocationToward::UBTTask_SetTargetLocationToward()
{
	NodeName = "Set Target Location Toward";
	Distance = 0.f;
	
	BlackboardKey.AddVectorFilter(
		this,
		GET_MEMBER_NAME_CHECKED(UBTTask_SetTargetLocationToward, BlackboardKey)
	);
	TowardLocation.AddVectorFilter(
		this,
		GET_MEMBER_NAME_CHECKED(UBTTask_SetTargetLocationToward, TowardLocation)
	);
}

FString UBTTask_SetTargetLocationToward::GetStaticDescription() const
{
	return FString::Printf(TEXT("Target: %s\nTowardLocation: %s\nDistance: %f"),
	                       *GetSelectedBlackboardKey().ToString(),
	                       *TowardLocation.SelectedKeyName.ToString(),
	                       Distance);
}

EBTNodeResult::Type UBTTask_SetTargetLocationToward::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController { OwnerComp.GetAIOwner() };
	UBlackboardComponent* BlackboardComponent { OwnerComp.GetBlackboardComponent() };
	
	if (IsValid(AIController) && IsValid(BlackboardComponent))
	{
		const FVector Direction = BlackboardComponent->GetValueAsVector(TowardLocation.SelectedKeyName);
		const FVector CurrentLocation = AIController->GetCharacter()->GetActorLocation();

		FVector TowardVector = Direction - CurrentLocation;
		TowardVector = TowardVector.GetSafeNormal() * Distance + Direction;

		const FVector ResultVector { TowardVector.X, TowardVector.Y, CurrentLocation.Z };
		
		BlackboardComponent->SetValueAsVector(GetSelectedBlackboardKey(), ResultVector);

		return FinishTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	
	return FinishTask(OwnerComp, EBTNodeResult::Failed);
}
