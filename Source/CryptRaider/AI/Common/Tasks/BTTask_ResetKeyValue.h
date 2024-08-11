// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTTask_Base.h"
#include "BTTask_ResetKeyValue.generated.h"

/**
 * 
 */
UCLASS()
class CRYPTRAIDER_API UBTTask_ResetKeyValue : public UBTTask_Base
{
	GENERATED_BODY()

public:
	UBTTask_ResetKeyValue();

public:
	virtual FString GetStaticDescription() const override;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
