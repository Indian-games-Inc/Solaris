// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTTask_Base.h"
#include "BTTask_SearchInRadius.generated.h"

/**
 * 
 */
UCLASS()
class CRYPTRAIDER_API UBTTask_SearchInRadius : public UBTTask_Base
{
	GENERATED_BODY()
public:
	UBTTask_SearchInRadius();

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;

private:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	float SearchRadius = 0;
};
