// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory.h"
#include "../Data/InventoryItemWrapper.h"

void UInventory::InitItemsArray()
{
	Items.Init(FInventoryItemWrapper(), Rows * Columns);
}


void UInventory::AddItem(const FInventoryItemWrapper& NewItem)
{
	for (auto& Item : Items)
	{
		if (Item.Data.Name.IsEmpty())
		{
			Item = NewItem;
			ItemsCount++;
			break;
		}
	}
}

TArray<FInventoryItemWrapper> UInventory::GetInventoryItems()
{
	return Items;
}

int UInventory::GetColumns()
{
	return Columns;
}

int UInventory::GetRows()
{
	return Rows;
}

int UInventory::GetItemsCount()
{
	return ItemsCount;
}

int UInventory::ToFlatIndex(int I, int J)
{
	return I * Rows + J;
}

void UInventory::SwapItems(int OldIndex, int NewIndex)
{
	const FInventoryItemWrapper ReplacementItem = Items[OldIndex];
	const FInventoryItemWrapper ReplacedItem = Items[NewIndex];

	Items[NewIndex] = ReplacementItem;
	Items[OldIndex] = ReplacedItem;
}

FInventoryItemWrapper UInventory::GetItemOnIndex(int Index)
{
	return Items[Index];
}

FInventoryItemWrapper UInventory::RemoveItemFromInventory(int Index)
{
	ItemsCount--;
	auto Item = Items[Index];
	Items[Index] = FInventoryItemWrapper();
	return Item;
}
