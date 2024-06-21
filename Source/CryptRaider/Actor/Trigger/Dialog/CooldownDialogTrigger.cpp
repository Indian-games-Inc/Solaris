#include "CooldownDialogTrigger.h"

#include "Components/BoxComponent.h"

void ACooldownDialogTrigger::SwitchTriggerState()
{
	TriggerBox->SetGenerateOverlapEvents(false);
	GetWorldTimerManager().SetTimer(DelayTimerHandle, [this]()
	{
		TriggerBox->SetGenerateOverlapEvents(true);
	}, PlayBackCooldown, false);
}
