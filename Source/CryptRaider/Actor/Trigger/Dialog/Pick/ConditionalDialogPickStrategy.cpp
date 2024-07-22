#include "ConditionalDialogPickStrategy.h"

bool UConditionalDialogPickStrategy::Check()
{
	UE_LOG(LogTemp, Warning,
	       TEXT("Called UConditionalDialogPickStrategy::Check, this function must be implemented in child classes"))
	return true;
}

FDataTableRowHandle UConditionalDialogPickStrategy::PickRandomDialog(TArray<FDataTableRowHandle> DialogList)
{
	const FRandomStream RandomStream(FDateTime::Now().GetTicks());
	return DialogList[RandomStream.RandRange(0, DialogList.Num() - 1)];
}


FDataTableRowHandle UConditionalDialogPickStrategy::GetDialog()
{
	return this->Check() ? PickRandomDialog(PositiveDialogList) : PickRandomDialog(NegativeDialogList);
}
