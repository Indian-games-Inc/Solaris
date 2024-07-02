// Fill out your copyright notice in the Description page of Project Settings.

#include "DialogTrigger.h"

#include "CryptRaider/Component/Inventory.h"
#include "CryptRaider/Player/BasePlayerController.h"

void ADialogTrigger::SendDialog(ABasePlayerController* Controller)
{
	SendDialogToHUD(Controller->GetHUD(), PickDialog());
	SwitchTriggerState();
}

void ADialogTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                    const FHitResult& SweepResult)
{
	const auto Controller = Cast<ABasePlayerController>(GetWorld()->GetFirstPlayerController());
	if (InventoryAware)
	{
		/**
		 * If item stored in Inventory and Has Item checked -> true
		 * If no item and not checked -> true
		 * otherwise should be false
		 */
		if (Controller->GetInventory()->HasItem(ItemId) == HasItem)
		{
			SendDialog(Controller);
		}
	}
	else
	{
		SendDialog(Controller);
	}
}

FDataTableRowHandle ADialogTrigger::PickDialog()
{
	return {};
}

void ADialogTrigger::SwitchTriggerState()
{
}
