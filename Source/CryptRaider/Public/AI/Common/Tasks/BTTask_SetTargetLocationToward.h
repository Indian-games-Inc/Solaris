#pragma once

#include "CoreMinimal.h"
#include "BTTask_Base.h"
#include "BTTask_SetTargetLocationToward.generated.h"


UCLASS()
class CRYPTRAIDER_API UBTTask_SetTargetLocationToward : public UBTTask_Base
{
	GENERATED_BODY()

public:
	UBTTask_SetTargetLocationToward();

	virtual FString GetStaticDescription() const override;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	FBlackboardKeySelector TowardLocation;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	float Distance;
};
