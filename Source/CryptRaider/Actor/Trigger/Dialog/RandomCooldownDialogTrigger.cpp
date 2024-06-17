// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomCooldownDialogTrigger.h"

#include "Components/BoxComponent.h"

void ARandomCooldownDialogTrigger::SwitchTriggerState()
{
	TriggerBox->SetGenerateOverlapEvents(false);
	GetWorldTimerManager().SetTimer(DelayTimerHandle, [this]()
	{
		TriggerBox->SetGenerateOverlapEvents(true);
	}, PlayBackCooldown, false);
}

FDataTableRowHandle ARandomCooldownDialogTrigger::PickDialog()
{
	const FRandomStream RandomStream(FDateTime::Now().GetTicks());
	return DialogRowList[RandomStream.RandRange(0, DialogRowList.Num() - 1)];
}
