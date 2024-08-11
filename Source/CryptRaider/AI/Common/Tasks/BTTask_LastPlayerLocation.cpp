// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_LastPlayerLocation.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "CryptRaider/Player/BaseCharacter.h"

UBTTask_LastPlayerLocation::UBTTask_LastPlayerLocation()
{
	NodeName = "Last Player Location";

	BlackboardKey.AddVectorFilter(
		this,
		GET_MEMBER_NAME_CHECKED(UBTTask_LastPlayerLocation, BlackboardKey)
	);
}

FString UBTTask_LastPlayerLocation::GetStaticDescription() const
{
	return FString::Printf(TEXT("TargetLocation: %s"), *GetSelectedBlackboardKey().ToString());
}

EBTNodeResult::Type UBTTask_LastPlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	const auto PlayerCharacter = Cast<ABaseCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());

	if (IsValid(BlackboardComponent) && IsValid(PlayerCharacter))
	{
		BlackboardComponent->SetValueAsVector(GetSelectedBlackboardKey(), PlayerCharacter->GetActorLocation());

		return FinishTask(OwnerComp, EBTNodeResult::Succeeded);
	}

	return FinishTask(OwnerComp, EBTNodeResult::Failed);
}