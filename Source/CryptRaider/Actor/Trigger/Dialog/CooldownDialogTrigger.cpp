// Fill out your copyright notice in the Description page of Project Settings.

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

FDataTableRowHandle ACooldownDialogTrigger::PickDialog()
{
	return DialogRow;
}
