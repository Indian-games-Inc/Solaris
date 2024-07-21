// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseDialogPickStrategy.h"

FDataTableRowHandle UBaseDialogPickStrategy::GetDialog()
{
	UE_LOG(LogTemp, Warning, TEXT("Called UBaseDialogPickStrategy::GetDialog, this function must be implemented in child classes"))
	return {};
}

