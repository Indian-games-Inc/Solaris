#include "AI/Common/Tasks/BTTask_SwitchStage.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTTask_SwitchStage::UBTTask_SwitchStage()
{
	NodeName = "Switch Stage";
	NewStage = EMonsterStage::None;
}

FString UBTTask_SwitchStage::GetStaticDescription() const
{
	const UEnum* EnumPtr = StaticEnum<EMonsterStage>();
	const FString StageString = EnumPtr->GetDisplayNameTextByValue(StaticCast<int64>(NewStage)).ToString();

	return FString::Printf(TEXT("Key: %s, New Stage: %s"),
	                       *GetSelectedBlackboardKey().ToString(),
	                       *StageString);
}

EBTNodeResult::Type UBTTask_SwitchStage::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComponent { OwnerComp.GetBlackboardComponent() };

	BlackboardComponent->SetValueAsEnum(GetSelectedBlackboardKey(), StaticCast<uint8>(NewStage));
	
	return FinishTask(OwnerComp, EBTNodeResult::Succeeded);
}
