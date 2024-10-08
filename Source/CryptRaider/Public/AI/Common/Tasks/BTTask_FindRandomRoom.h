#pragma once

#include "CoreMinimal.h"
#include "BTTask_Base.h"
#include "BTTask_FindRandomRoom.generated.h"


UCLASS()
class CRYPTRAIDER_API UBTTask_FindRandomRoom : public UBTTask_Base
{
	GENERATED_BODY()

public:
	UBTTask_FindRandomRoom();

public:
	virtual FString GetStaticDescription() const override;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Target", meta=(AllowPrivateAccess = "true"))
	TSubclassOf<AActor> TargetActorClass;
};
