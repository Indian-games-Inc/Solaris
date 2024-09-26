#include "AI/Common/Tasks/BTTask_ResetKeyValue.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ResetKeyValue::UBTTask_ResetKeyValue()
{
	NodeName = "Reset Key Value";
}

FString UBTTask_ResetKeyValue::GetStaticDescription() const
{
	return FString::Printf(TEXT("Key: %s"), *GetSelectedBlackboardKey().ToString());
}

EBTNodeResult::Type UBTTask_ResetKeyValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (UBlackboardComponent* BlackboardComponent { OwnerComp.GetBlackboardComponent() }; IsValid(BlackboardComponent))
	{
		BlackboardComponent->ClearValue(GetSelectedBlackboardKey());

		return FinishTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	return FinishTask(OwnerComp, EBTNodeResult::Failed);
}
