// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory.h"
#include "CryptRaider/Data/InventoryItemWrapper.h"

void UInventory::InitItemsArray()
{
	Items.Init(FInventoryItemWrapper(), Rows * Columns);
}


void UInventory::AddItem(const FInventoryItemWrapper& NewItem)
{
	if (NewItem.Data.Name.IsEmpty())
		return;

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

TArray<FInventoryItemWrapper> UInventory::GetItems()
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
	Items[OldIndex] = Items[NewIndex];
	Items[NewIndex] = ReplacementItem;
}

FInventoryItemWrapper UInventory::GetItemOnIndex(int Index)
{
	return Items[Index];
}

FInventoryItemWrapper UInventory::RemoveItem(int Index)
{
	ItemsCount--;
	auto Item = Items[Index];
	Items[Index] = FInventoryItemWrapper();
	return Item;
}

bool UInventory::IsFull()
{
	return ItemsCount == Items.Num();
}

bool UInventory::HasItem(const FString& ItemId)
{
	for (auto Item : Items)
	{
		if (Item.Data.ID == ItemId)
		{
			return true;
		}
	}
	return false;
}
