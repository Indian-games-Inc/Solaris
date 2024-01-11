// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory.h"
#include "ItemData.h"

// Add item to inventory
void UInventory::AddItem(const FItemData& Item)
{
	this->InventoryItems.Add(Item);
}

TArray<FItemData> UInventory::GetInventoryItems()
{
	return this->InventoryItems;
}
