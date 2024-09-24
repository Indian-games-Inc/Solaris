// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Trigger/Dialog/Pick/RandomListDialogPickStrategy.h"

FDataTableRowHandle URandomListDialogPickStrategy::GetDialog()
{
	const FRandomStream RandomStream(FDateTime::Now().GetTicks());
	return DialogList[RandomStream.RandRange(0, DialogList.Num() - 1)];
}
