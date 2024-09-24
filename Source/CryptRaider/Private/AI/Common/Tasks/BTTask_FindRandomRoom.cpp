// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Common/Tasks/BTTask_FindRandomRoom.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTTask_FindRandomRoom::UBTTask_FindRandomRoom()
{
	NodeName = TEXT("Find Random Room");

	BlackboardKey.AddVectorFilter(
		this,
		GET_MEMBER_NAME_CHECKED(UBTTask_FindRandomRoom, BlackboardKey)
	);
}

FString UBTTask_FindRandomRoom::GetStaticDescription() const
{
	FString TargetActorClassName = "None";

	if (IsValid(TargetActorClass))
	{
		TargetActorClassName = TargetActorClass->GetName();
	}

	return FString::Printf(TEXT("Vector: %s\nTargetActorClass: %s"), *GetSelectedBlackboardKey().ToString(), *TargetActorClassName);
}

EBTNodeResult::Type UBTTask_FindRandomRoom::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	
	if (IsValid(BlackboardComponent) && IsValid(TargetActorClass))
	{
		TArray<AActor*> OutActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), TargetActorClass,OutActors);

		if (OutActors.IsEmpty())
		{
			return FinishTask(OwnerComp, EBTNodeResult::Failed);
		}

		const FRandomStream RandomStream(FDateTime::Now().GetTicks());

		const AActor* TargetActor = OutActors[RandomStream.RandRange(0,OutActors.Num() - 1)];

		BlackboardComponent->SetValueAsVector(GetSelectedBlackboardKey(), TargetActor->GetActorLocation());

		return FinishTask(OwnerComp, EBTNodeResult::Succeeded);
	}

	return FinishTask(OwnerComp, EBTNodeResult::Failed);
}