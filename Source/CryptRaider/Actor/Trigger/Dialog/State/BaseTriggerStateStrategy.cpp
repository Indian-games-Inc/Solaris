// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTriggerStateStrategy.h"

#include "WorldPartition/ContentBundle/ContentBundleLog.h"

bool UBaseTriggerStateStrategy::IsActive()
{
	UE_LOG(LogTemp, Warning, TEXT("UBaseTriggerStateStrategy::IsActive called"));
	return true;
}

void UBaseTriggerStateStrategy::OnTrigger()
{
	UE_LOG(LogTemp, Warning, TEXT("UBaseTriggerStateStrategy::OnTrigger called"));
}

