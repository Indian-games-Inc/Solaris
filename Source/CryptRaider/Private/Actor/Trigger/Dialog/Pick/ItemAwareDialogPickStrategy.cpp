#include "Actor/Trigger/Dialog/Pick/ItemAwareDialogPickStrategy.h"

#include "Player/Components/Inventory.h"
#include "Player/BasePlayerController.h"

bool UItemAwareDialogPickStrategy::Check()
{
	const auto Controller = Cast<ABasePlayerController>(GetWorld()->GetFirstPlayerController());
	return Controller->GetInventory()->HasItem(ItemId);
}
