// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Trigger/Dialog/State/CooldownStrategy.h"

bool UCooldownStrategy::IsActive()
{
	return Active;
}

void UCooldownStrategy::OnTrigger()
{
	if (auto& TimerManager = GetOwner()->GetWorldTimerManager(); !TimerManager.IsTimerActive(DelayTimerHandle))
	{
		Active = false;
		TimerManager.SetTimer(
			DelayTimerHandle,
			[this]()
			{
				Active = true;
			},
			PlayBackCooldown, false);
	}
}
