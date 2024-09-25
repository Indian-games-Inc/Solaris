#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "AI/Common/Enum/MonsterStage.h"
#include "BTService_StageUpdate.generated.h"


UCLASS()
class CRYPTRAIDER_API UBTService_StageUpdate : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_StageUpdate();
	virtual FString GetStaticDescription() const override;

protected:
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	UFUNCTION()
	void UpdateStage(UBehaviorTreeComponent* OwnerComp);

	void ResetStageTimer(UBehaviorTreeComponent& OwnerComp);

	EMonsterStage GetCurrentStage(UBehaviorTreeComponent* OwnerComp) const;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	FBlackboardKeySelector StageKey;

	UPROPERTY()
	EMonsterStage SavedStage;
	
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	float StageUpdateInterval;

	UPROPERTY()
	FTimerHandle StageUpdateTimerHandle;
};
