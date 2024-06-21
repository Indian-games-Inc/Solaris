// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomCooldownDialogTrigger.h"

FDataTableRowHandle ARandomCooldownDialogTrigger::PickDialog()
{
	const FRandomStream RandomStream(FDateTime::Now().GetTicks());
	return DialogRowList[RandomStream.RandRange(0, DialogRowList.Num() - 1)];
}
