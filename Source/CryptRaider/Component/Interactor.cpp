// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactor.h"

#include "Hand.h"
#include "CryptRaider/Interface/Interactable.h"
#include "CryptRaider/Player/BasePlayerController.h"

void UInteractor::Interact()
{
	if (const auto& HitResult = GetHand()->GetInteractableInReach(); HitResult.IsSet())
	{
		if (IInteractable* Actor = Cast<IInteractable>(HitResult->GetActor()))
		{
			Actor->Interact();
		}	
	}
}

FText UInteractor::ConstructHint() const
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
			if (const auto* Interactable = Cast<IInteractable>(HitResult->GetActor());
				Interactable)
				return FText::FromString(FString::Printf(
					TEXT("[%s] %s"),
					*Controller->InteractKey()->ToString(),
					*Interactable->HintMessage()
				));
		}
	}
	
	return {};
}
