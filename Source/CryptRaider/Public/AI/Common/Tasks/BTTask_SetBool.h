// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTTask_Base.h"
#include "BTTask_SetBool.generated.h"

/**
 * 
 */
UCLASS()
class CRYPTRAIDER_API UBTTask_SetBool : public UBTTask_Base
{
	GENERATED_BODY()

public:
	UBTTask_SetBool();

	virtual FString GetStaticDescription() const override;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditInstanceOnly, Category="AI", meta = (AllowPrivateAccess = "true"))
	bool Value;
};
