#include "Actor/Trigger/Dialog/Pick/BaseDialogPickStrategy.h"

FDataTableRowHandle UBaseDialogPickStrategy::GetDialog()
{
	UE_LOG(LogTemp, Warning, TEXT("Called UBaseDialogPickStrategy::GetDialog, this function must be implemented in child classes"))
	return {};
}

