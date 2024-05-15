// Fill out your copyright notice in the Description page of Project Settings.

#include "Picker.h"
#include "CryptRaider/Actor/Item.h"
#include "CryptRaider/Data/InventoryItemWrapper.h"


TOptional<FInventoryItemWrapper> UPicker::PickItem(const FHitResult& HitResult)
{
	if (AItem* Item = Cast<AItem>(HitResult.GetActor()))
	{
		return FInventoryItemWrapper {Item->Pick(), Item->GetClass()};
	}

	return {};
}
