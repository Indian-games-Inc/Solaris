// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/Components/Picker.h"

#include "GameFramework/Character.h"

#include "Player/Components/Hand.h"
#include "Actor/Item/Item.h"
#include "Data/InventoryItemWrapper.h"
#include "Player/BasePlayerController.h"


void UPicker::Interact()
{
	if (const auto& Item = PickItem(); Item.IsSet())
	{
		OnItemPicked.Broadcast(Item.GetValue());
	}
}

FText UPicker::ConstructHint() const
{
	const auto* Controller = GetController();
	if (!IsValid(Controller))
	{
		return {};
	}

	if (const UHand* Hand = GetHand(); IsValid(Hand))
	{
		if (const auto& HitResult = Hand->GetInteractableInReach();
			HitResult.IsSet())
		{
			if (const auto* Item = Cast<AItem>(HitResult->GetActor());
				IsValid(Item))
				return FText::FromString(FString::Printf(
					TEXT("[%s] Pickup %s"),
					*Controller->InteractKey()->ToString(),
					*Item->HintMessage()
				));
		}
	}
	return {};
}

TOptional<FInventoryItemWrapper> UPicker::PickItem()
{
	if (const auto* Hand = GetHand(); IsValid(Hand))
	{
		if (const auto& HitResult = Hand->GetInteractableInReach(); HitResult.IsSet())
		{
			if (AItem* Item = Cast<AItem>(HitResult->GetActor()))
			{
				return FInventoryItemWrapper {Item->Pick(), Item->GetClass()};
			}
		}
	}
	return {};
}
