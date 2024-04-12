// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorItemLock.h"

#include "Door.h"
#include "CryptRaider/Character/BaseCharacter.h"
#include "CryptRaider/Component/Inventory.h"
#include "CryptRaider/Data/InventoryItemWrapper.h"

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
	if (!HasKey())
	{
		return "You don't have access to this door";
	}

	return Door->IsClosed() ? "Unlock" : "Block";
}

bool ADoorItemLock::HasKey() const
{
	auto Items = Cast<ABaseCharacter>(
		             GetWorld()->
		             GetFirstPlayerController()->
		             GetCharacter())->
	             GetInventory()->
	             GetItems();

	for (auto& Wrapper : Items)
	{
		if (Wrapper.Data.ID == ItemID)
		{
			return true;
		}
	}

	return false;
}
