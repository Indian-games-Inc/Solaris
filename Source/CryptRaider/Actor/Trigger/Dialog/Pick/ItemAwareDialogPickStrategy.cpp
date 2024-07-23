#include "ItemAwareDialogPickStrategy.h"

#include "CryptRaider/Component/Inventory.h"
#include "CryptRaider/Player/BasePlayerController.h"

bool UItemAwareDialogPickStrategy::Check()
{
	const auto Controller = Cast<ABasePlayerController>(GetWorld()->GetFirstPlayerController());
	return Controller->GetInventory()->HasItem(ItemId);
}
