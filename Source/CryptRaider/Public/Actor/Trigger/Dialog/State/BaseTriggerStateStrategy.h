#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/DialogStateStrategy.h"
#include "BaseTriggerStateStrategy.generated.h"


UCLASS(HideDropdown, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRYPTRAIDER_API UBaseTriggerStateStrategy : public UActorComponent, public IDialogStateStrategy
{
	GENERATED_BODY()

public:
	virtual bool IsActive() override;
	virtual void OnTrigger() override;
};
