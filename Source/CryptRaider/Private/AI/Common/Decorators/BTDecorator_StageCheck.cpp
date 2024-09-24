#include "AI/Common/Decorators/BTDecorator_StageCheck.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_StageCheck::UBTDecorator_StageCheck()
{
	NodeName = "Stage Check";
	Stage = EMonsterStage::None;
}

FString UBTDecorator_StageCheck::GetStaticDescription() const
{
	const UEnum* EnumPtr = StaticEnum<EMonsterStage>();
	const FString StageString = EnumPtr->GetDisplayNameTextByValue(StaticCast<int64>(Stage)).ToString();

	return FString::Printf(TEXT("Key: %s, Stage: %s"),
						   *GetSelectedBlackboardKey().ToString(),
						   *StageString);
}

bool UBTDecorator_StageCheck::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const UBlackboardComponent* BlackboardComponent { OwnerComp.GetBlackboardComponent() };
	const EMonsterStage CurrentStage = StaticCast<EMonsterStage>(BlackboardComponent->GetValueAsEnum(GetSelectedBlackboardKey()));

	return CurrentStage == Stage;
}
