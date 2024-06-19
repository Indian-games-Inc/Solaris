#pragma once
#include "DialogTrigger.h"
#include "Cooldownable.generated.h"

UCLASS()
class ACooldownable : public ADialogTrigger
{
	GENERATED_BODY()

protected:
	virtual void SwitchTriggerState() override;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Dialog Trigger")
	float PlayBackCooldown;

private:
	FTimerHandle DelayTimerHandle;
};
