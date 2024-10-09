#include "Actor/Trigger/Dialog/Pick/ItemAwareDialogPickStrategy.h"

#include "Player/Components/Inventory.h"
#include "Player/BasePlayerController.h"

bool UItemAwareDialogPickStrategy::Check()
{
	if (const auto* Inventory = GetWorld()->GetFirstPlayerController()->FindComponentByClass<UInventory>();
		IsValid(Inventory))
	{
		return Inventory->HasItem(ItemId);
	}
	return false;
}
