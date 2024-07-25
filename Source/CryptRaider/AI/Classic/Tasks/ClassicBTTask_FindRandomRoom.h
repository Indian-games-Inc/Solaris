// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "ClassicBTTask_FindRandomRoom.generated.h"

/**
 * 
 */
UCLASS()
class CRYPTRAIDER_API UClassicBTTask_FindRandomRoom : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	UClassicBTTask_FindRandomRoom();

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Target", meta=(AllowPrivateAccess = "true"))
	TSubclassOf<AActor> TargetActorClass;
};
