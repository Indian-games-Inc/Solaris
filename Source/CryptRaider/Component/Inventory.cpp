// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory.h"
#include "../Data/ItemData.h"

void UInventory::InitItemsArray()
{
	Items.Init(FItemData(), Rows * Columns);
}


void UInventory::AddItem(const FItemData& Item)
{
	for (int i = 0; i < Rows * Columns; ++i)
	{
		//Checks if slot is empty ???
		if (Items[i].Name == "")
		{
			Items[i] = Item;
			ItemsCount++;
			break;
		}
	}
}

TArray<FItemData> UInventory::GetInventoryItems()
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
	const FItemData ReplacementItem = Items[OldIndex];
	const FItemData ReplacedItem = Items[NewIndex];

	Items[NewIndex] = ReplacementItem;
	Items[OldIndex] = ReplacedItem;
}

