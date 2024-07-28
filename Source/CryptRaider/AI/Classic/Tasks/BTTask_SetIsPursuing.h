// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_SetIsPursuing.generated.h"

/**
 * 
 */
UCLASS()
class CRYPTRAIDER_API UBTTask_SetIsPursuing : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_SetIsPursuing();

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;

private:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Value", meta=(AllowPrivateAccess="true"))
	bool Value = false;
};
