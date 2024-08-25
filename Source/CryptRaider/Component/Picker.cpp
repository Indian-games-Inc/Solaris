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

	if (const auto& HintMessage = ConstructHintMessage(); !HintMessage.IsEmpty())
	{
		OnHintUpdated.Broadcast(ConstructHintMessage());	
	}
}

TOptional<FInventoryItemWrapper> UPicker::PickItem(const FHitResult& HitResult) // TODO Refactor regarding GetHand
{
	if (AItem* Item = Cast<AItem>(HitResult.GetActor()))
	{
		return FInventoryItemWrapper {Item->Pick(), Item->GetClass()}; // TODO Send pickup event to controller?
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