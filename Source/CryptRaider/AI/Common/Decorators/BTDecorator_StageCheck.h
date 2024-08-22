// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "CryptRaider/AI/Common/Enum/MonsterStage.h"
#include "BTDecorator_StageCheck.generated.h"

/**
 * 
 */
UCLASS()
class CRYPTRAIDER_API UBTDecorator_StageCheck : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTDecorator_StageCheck();

	virtual FString GetStaticDescription() const override;

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

private:
	UPROPERTY(EditInstanceOnly, Category="AI", meta = (AllowPrivateAccess = "true"))
	EMonsterStage Stage;
};
