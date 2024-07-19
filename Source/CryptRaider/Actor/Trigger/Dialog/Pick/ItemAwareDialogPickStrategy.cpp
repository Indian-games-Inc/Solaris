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
		if ((PostDialogList.Num() > 0))
		{
			Dialog = PostDialogList[RandomStream.RandRange(0, PostDialogList.Num() - 1)];
		}
	}
	else
	{
		if (PreDialogList.Num() > 0)
		{
			Dialog = PreDialogList[RandomStream.RandRange(0, PreDialogList.Num() - 1)];
		}
	}
	return Dialog;
}
