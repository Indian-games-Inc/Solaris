#pragma once
#include "DialogTrigger.h"
#include "CooldownDialogTrigger.generated.h"

UCLASS()
class ACooldownDialogTrigger : public ADialogTrigger
{
	GENERATED_BODY()

protected:
	virtual void SwitchTriggerState() override;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Dialog Trigger")
	float PlayBackCooldown;

private:
	FTimerHandle DelayTimerHandle;
};
