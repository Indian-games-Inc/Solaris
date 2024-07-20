// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemAwareDialogPickStrategy.h"

#include "CryptRaider/Component/Inventory.h"
#include "CryptRaider/Player/BasePlayerController.h"

FDataTableRowHandle UItemAwareDialogPickStrategy::GetDialog()
{
	const FRandomStream RandomStream(FDateTime::Now().GetTicks());
	const auto Controller = Cast<ABasePlayerController>(GetWorld()->GetFirstPlayerController());
	FDataTableRowHandle Dialog = {};
	if (Controller->GetInventory()->HasItem(ItemId))
	{
		if (!PositiveDialogList.IsEmpty())
		{
			Dialog = PositiveDialogList[RandomStream.RandRange(0, PositiveDialogList.Num() - 1)];
		}
	}
	else
	{
		if (!NegativeDialogList.IsEmpty())
		{
			Dialog = NegativeDialogList[RandomStream.RandRange(0, NegativeDialogList.Num() - 1)];
		}
	}
	return Dialog;
}
