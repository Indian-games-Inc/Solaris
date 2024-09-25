#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "AI/Common/Enum/MonsterStage.h"
#include "BTDecorator_StageCheck.generated.h"


UCLASS()
class CRYPTRAIDER_API UBTDecorator_StageCheck : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTDecorator_StageCheck();

	virtual FString GetStaticDescription() const override;

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

private:
	UPROPERTY(EditInstanceOnly, Category="AI", meta = (AllowPrivateAccess = "true"))
	EMonsterStage Stage;
};
