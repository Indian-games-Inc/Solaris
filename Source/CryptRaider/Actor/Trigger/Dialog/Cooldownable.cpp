#include "Cooldownable.h"

#include "Components/BoxComponent.h"

void ACooldownable::SwitchTriggerState()
{
	TriggerBox->SetGenerateOverlapEvents(false);
	GetWorldTimerManager().SetTimer(DelayTimerHandle, [this]()
	{
		TriggerBox->SetGenerateOverlapEvents(true);
	}, PlayBackCooldown, false);
}
