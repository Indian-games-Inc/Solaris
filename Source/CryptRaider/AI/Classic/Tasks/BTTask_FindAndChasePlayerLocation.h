// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTTask_Base.h"
#include "BTTask_FindAndChasePlayerLocation.generated.h"

/**
 * 
 */
UCLASS()
class CRYPTRAIDER_API UBTTask_FindAndChasePlayerLocation : public UBTTask_Base
{
	GENERATED_BODY()

public:
	UBTTask_FindAndChasePlayerLocation();

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;
};
