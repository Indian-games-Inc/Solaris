// Fill out your copyright notice in the Description page of Project Settings.


#include "CryptRaider/AI/Classic/Tasks/BTTask_FindRandomRoom.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTTask_FindRandomRoom::UBTTask_FindRandomRoom()
{
	NodeName = TEXT("Find Random Room");

	BlackboardKey.AddVectorFilter(this,
		GET_MEMBER_NAME_CHECKED(UBTTask_FindRandomRoom, BlackboardKey)
	);
}

EBTNodeResult::Type UBTTask_FindRandomRoom::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController { OwnerComp.GetAIOwner() }; 
	
	if (IsValid(TargetActorClass))
	{
		TArray<AActor*> OutActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), TargetActorClass,OutActors);

		if (OutActors.IsEmpty())
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
			return EBTNodeResult::Failed;
		}

		const FRandomStream RandomStream(FDateTime::Now().GetTicks());

		const AActor* TargetActor = OutActors[RandomStream.RandRange(0,OutActors.Num() - 1)];

		AIController->GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, TargetActor->GetActorLocation());
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

FString UBTTask_FindRandomRoom::GetStaticDescription() const
{
	FString TargetActorClassName = "None";

	if (IsValid(TargetActorClass))
	{
		TargetActorClassName = TargetActorClass->GetName();
	}

	return FString::Printf(TEXT("Vector: %s, TargetActorClass: %s"), *BlackboardKey.SelectedKeyName.ToString(), *TargetActorClassName);
}
