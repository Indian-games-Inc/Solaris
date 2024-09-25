#include "Player/Components/BaseHandInteractor.h"

#include "GameFramework/Character.h"
#include "Player/Components/Hand.h"
#include "Player/BasePlayerController.h"


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