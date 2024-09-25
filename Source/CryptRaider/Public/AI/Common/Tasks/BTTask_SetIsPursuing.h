#pragma once

#include "CoreMinimal.h"
#include "BTTask_Base.h"
#include "BTTask_SetIsPursuing.generated.h"


UCLASS()
class CRYPTRAIDER_API UBTTask_SetIsPursuing : public UBTTask_Base
{
	GENERATED_BODY()
public:
	UBTTask_SetIsPursuing();

public:
	virtual FString GetStaticDescription() const override;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Value", meta=(AllowPrivateAccess="true"))
	bool Value = false;
};
