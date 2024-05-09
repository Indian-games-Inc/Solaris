// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorLocker.h"

#include "Door.h"
#include "CryptRaider/Component/Inventory.h"
#include "CryptRaider/Data/InventoryItemWrapper.h"
#include "CryptRaider/Player/BasePlayerController.h"

void ADoorLocker::Interact()
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

FString ADoorLocker::HintMessage() const
{
	if (!HasKey())
	{
		return "You don't have access to this door";
	}

	return Door->IsClosed() ? "Unlock" : "Block";
}

bool ADoorLocker::HasKey() const
{
	if (auto* Controller = Cast<ABasePlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		auto Items = Controller->GetInventory()->GetItems();

		for (const auto& Wrapper : Items)
		{
			if (Wrapper.Data.ID == ItemID)
			{
				return true;
			}
		}
	}
	return false;
}
