// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactor.h"

#include "Hand.h"
#include "CryptRaider/Interface/Interactable.h"
#include "CryptRaider/Player/BasePlayerController.h"
#include "GameFramework/Character.h"

UInteractor::UInteractor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UInteractor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

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

UHand* UInteractor::GetHand() const
{
	return GetOwner()->FindComponentByClass<UHand>();
}

ABasePlayerController* UInteractor::GetController() const
{
	if (const auto* Character = Cast<ACharacter>(GetOwner()); IsValid(Character))
	{
		return Cast<ABasePlayerController>(Character->GetController());
	}

	return nullptr;
}

FText UInteractor::ConstructHintMessage() const
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
