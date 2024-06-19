// Fill out your copyright notice in the Description page of Project Settings.


#include "SingleFire.h"

#include "Components/BoxComponent.h"

/**
 * Returns false, and assures that dialog is triggered only once
 */
void ASingleFire::SwitchTriggerState()
{
	TriggerBox->SetGenerateOverlapEvents(false);
}

/**
 * Simply returns attached DialogRow
 * @return FDataTableRowHandle attached to trigger
 */
FDataTableRowHandle ASingleFire::PickDialog()
{
	return DialogRow;
}
