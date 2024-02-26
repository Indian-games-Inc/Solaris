// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory.h"
#include "../Data/ItemData.h"

void UInventory::InitItemsArray()
{
	Items.Init(FItemData(), Rows * Columns);
}


void UInventory::AddItem(const FItemData& Item)
{
	for (auto& Data : Items)
	{
		if (Data.Name.IsEmpty())
		{
			Data = Item;
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

FItemData UInventory::GetItemOnIndex(int Index)
{
	return Items[Index];
}

FItemData UInventory::RemoveItemFromInventory(int Index)
{
	auto Item = Items[Index];
	Items[Index] = FItemData();
	return Item;
}
