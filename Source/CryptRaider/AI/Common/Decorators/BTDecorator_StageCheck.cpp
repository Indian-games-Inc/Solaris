// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_StageCheck.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_StageCheck::UBTDecorator_StageCheck()
{
	NodeName = "Stage Check";
	Stage = EMonsterStage::None;
}

FString UBTDecorator_StageCheck::GetStaticDescription() const
{
	const UEnum* EnumPtr = StaticEnum<EMonsterStage>();
	const FString StageString = EnumPtr->GetDisplayNameTextByValue(static_cast<int64>(Stage)).ToString();

	return FString::Printf(TEXT("Key: %s, Stage: %s"),
						   *GetSelectedBlackboardKey().ToString(),
						   *StageString);
}

bool UBTDecorator_StageCheck::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const UBlackboardComponent* BlackboardComponent { OwnerComp.GetBlackboardComponent() };
	const EMonsterStage CurrentStage = static_cast<EMonsterStage>(BlackboardComponent->GetValueAsEnum(GetSelectedBlackboardKey()));

	return CurrentStage == Stage;
}
