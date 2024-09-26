#include "Actor/Door/DoorItemLock.h"

#include "Actor/Door/Door.h"
#include "Player/Components/Inventory.h"
#include "Data/InventoryItemWrapper.h"
#include "Player/BasePlayerController.h"

void ADoorItemLock::Interact()
{
	if (!Door || ItemID.IsEmpty())
	{
		UE_LOG(LogActor, Warning, TEXT("Failed to interact, either Door is not set or ItemID missing"));
		return;
	}

	if (HasKey())
	{
		Door->IsClosed() ? Door->Open() : Door->Close();
	}
}

FString ADoorItemLock::HintMessage() const
{

	if (!Door)
	{
		UE_LOG(LogActor, Warning, TEXT("Failed to generate hint,Door is not set"));
		return "Error";
	}
	
	if (!HasKey())
	{
		return "You don't have access to this door";
	}

	return Door->IsClosed() ? "Unlock" : "Block";
}

bool ADoorItemLock::HasKey() const
{
	if (const auto* Inventory = GetWorld()->GetFirstPlayerController()->FindComponentByClass<UInventory>();
		IsValid(Inventory))
	{
		return Inventory->HasItem(ItemID);
	}
	return false;
}
