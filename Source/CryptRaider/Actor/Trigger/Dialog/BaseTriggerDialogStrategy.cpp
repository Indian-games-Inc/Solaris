// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTriggerDialogStrategy.h"

FDataTableRowHandle UBaseTriggerDialogStrategy::GetDialog()
{
	UE_LOG(LogTemp, Warning, TEXT("Called UBaseTriggerDialogStrategy::GetDialog, this function must be implemented in child classes"))
	return {};
}

