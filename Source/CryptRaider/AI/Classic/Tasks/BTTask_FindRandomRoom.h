// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTTask_Base.h"
#include "BTTask_FindRandomRoom.generated.h"

/**
 * 
 */
UCLASS()
class CRYPTRAIDER_API UBTTask_FindRandomRoom : public UBTTask_Base
{
	GENERATED_BODY()

public:
	UBTTask_FindRandomRoom();

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Target", meta=(AllowPrivateAccess = "true"))
	TSubclassOf<AActor> TargetActorClass;
};
