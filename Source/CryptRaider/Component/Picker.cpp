// Fill out your copyright notice in the Description page of Project Settings.

#include "Picker.h"

#include "Hand.h"
#include "CryptRaider/Actor/Item/Item.h"
#include "CryptRaider/Data/InventoryItemWrapper.h"
#include "CryptRaider/Player/BasePlayerController.h"
#include "GameFramework/Character.h"


UPicker::UPicker()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UPicker::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPicker::Interact()
{
	if (const auto& Item = PickItem(); Item.IsSet())
	{
		OnItemPicked.Broadcast(Item.GetValue());
	}
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

UHand* UPicker::GetHand() const
{
	return GetOwner()->FindComponentByClass<UHand>();
}

ABasePlayerController* UPicker::GetController() const
{
	if (const auto* Character = Cast<ACharacter>(GetOwner()); IsValid(Character))
	{
		return Cast<ABasePlayerController>(Character->GetController());
	}

	return nullptr;
}

FText UPicker::ConstructHintMessage() const
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