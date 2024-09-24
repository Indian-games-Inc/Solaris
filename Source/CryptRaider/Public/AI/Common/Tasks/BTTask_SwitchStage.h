#pragma once

#include "CoreMinimal.h"
#include "BTTask_Base.h"
#include "AI/Common/Enum/MonsterStage.h"
#include "BTTask_SwitchStage.generated.h"


UCLASS()
class CRYPTRAIDER_API UBTTask_SwitchStage : public UBTTask_Base
{
	GENERATED_BODY()

public:
	UBTTask_SwitchStage();

	virtual FString GetStaticDescription() const override;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditInstanceOnly, Category= "AI", meta = (AllowPrivateAccess = "true"))
	EMonsterStage NewStage;
};
