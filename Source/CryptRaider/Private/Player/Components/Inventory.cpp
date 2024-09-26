#include "Player/Components/Inventory.h"
#include "Data/InventoryItemWrapper.h"

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

TArray<FInventoryItemWrapper> UInventory::GetItems() const
{
	return Items;
}

int UInventory::GetColumns() const
{
	return Columns;
}

int UInventory::GetRows() const
{
	return Rows;
}

int UInventory::GetItemsCount() const
{
	return ItemsCount;
}

int UInventory::ToFlatIndex(int I, int J)
{
	return I * Rows + J;
}

void UInventory::SwapItems(int OldIndex, int NewIndex)
{
	std::swap(Items[OldIndex], Items[NewIndex]);
}

FInventoryItemWrapper UInventory::GetItemOnIndex(int Index) const
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

bool UInventory::IsFull() const
{
	return ItemsCount == Items.Num();
}

bool UInventory::HasItem(const FString& ItemId) const
{
	for (const auto& [Data, Class] : Items)
	{
		if (Data.ID == ItemId)
		{
			return true;
		}
	}
	return false;
}
