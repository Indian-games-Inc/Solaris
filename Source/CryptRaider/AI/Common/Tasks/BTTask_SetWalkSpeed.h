// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTTask_Base.h"
#include "BTTask_SetWalkSpeed.generated.h"

/**
 * 
 */
UCLASS()
class CRYPTRAIDER_API UBTTask_SetWalkSpeed : public UBTTask_Base
{
	GENERATED_BODY()

public:
	UBTTask_SetWalkSpeed();

public:
	virtual FString GetStaticDescription() const override;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	float MaxWalkSpeed = 0;
};
