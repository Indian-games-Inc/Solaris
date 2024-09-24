#pragma once

#include "CoreMinimal.h"
#include "BaseTriggerStateStrategy.h"
#include "Components/ActorComponent.h"
#include "Interface/DialogStateStrategy.h"
#include "SingleShotStrategy.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRYPTRAIDER_API USingleShotStrategy : public UBaseTriggerStateStrategy
{
	GENERATED_BODY()

public:
	virtual bool IsActive() override;
	virtual void OnTrigger() override;

private:
	UPROPERTY()
	bool Active = true;
};
