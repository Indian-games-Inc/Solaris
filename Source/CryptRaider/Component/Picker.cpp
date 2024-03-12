// Fill out your copyright notice in the Description page of Project Settings.

#include "Picker.h"
#include "../Actor/Item.h"
#include "../Data/InventoryItemWrapper.h"


TOptional<FInventoryItemWrapper> UPicker::PickItem(const FHitResult& HitResult)
{
	if (AItem* Item = Cast<AItem>(HitResult.GetActor()))
	{
		return FInventoryItemWrapper {Item->Pick(), Item->GetClass()};
	}

	return {};
}
