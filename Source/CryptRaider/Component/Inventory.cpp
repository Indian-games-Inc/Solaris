// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory.h"
#include "../Data/ItemData.h"

void UInventory::AddItem(const FItemData& Item)
{
	InventoryItems.Add(Item);
	InventoryWeight += Item.Weight;
}

TArray<FItemData> UInventory::GetInventoryItems()
{
	return InventoryItems;
}

float UInventory::GetTotalWeight()
{
	return InventoryWeight;
}
