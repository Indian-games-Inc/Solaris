// Fill out your copyright notice in the Description page of Project Settings.


#include "CooldownStrategy.h"

bool UCooldownStrategy::IsActive()
{
	return Active;
}

void UCooldownStrategy::OnTrigger()
{
	Active = false;
	GetOwner()->GetWorldTimerManager().SetTimer(
		DelayTimerHandle,
		[this]()
		{
			Active = true;
		},
		PlayBackCooldown, false);
}
