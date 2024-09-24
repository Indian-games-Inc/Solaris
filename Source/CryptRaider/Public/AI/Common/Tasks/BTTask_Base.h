#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_Base.generated.h"


UCLASS()
class CRYPTRAIDER_API UBTTask_Base : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_Base() = default;

public:
	virtual FString GetStaticDescription() const override;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	EBTNodeResult::Type FinishTask(UBehaviorTreeComponent& OwnerComp, EBTNodeResult::Type ResultType) const;
};
