// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseHandInteractor.h"

#include "Hand.h"
#include "CryptRaider/Player/BasePlayerController.h"
#include "GameFramework/Character.h"

void UBaseHandInteractor::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("UBaseHandInteractor::Interact() called, should be implemented in child classes"));
}

FText UBaseHandInteractor::ConstructHint() const
{
	UE_LOG(LogTemp, Warning, TEXT("UBaseHandInteractor::Interact() called, should be implemented in child classes"));
	return {};
}

UHand* UBaseHandInteractor::GetHand() const
{
	return GetOwner()->FindComponentByClass<UHand>();
}

ABasePlayerController* UBaseHandInteractor::GetController() const
{
	if (const auto* Character = Cast<ACharacter>(GetOwner()); IsValid(Character))
	{
		return Cast<ABasePlayerController>(Character->GetController());
	}

	return nullptr;
}