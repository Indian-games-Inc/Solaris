#include "Player/Components/HintProducer.h"

#include "Player/Components/Grabber.h"
#include "Player/Components/Interactor.h"
#include "Player/Components/Picker.h"


UHintProducer::UHintProducer()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHintProducer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (const auto& HintMessage = ConstructHint(); !HintMessage.IsEmpty())
	{
		OnHintUpdated.Broadcast(HintMessage);
	}
	else
	{
		OnHintUpdated.Broadcast(FText {});
	}
}

FText UHintProducer::ConstructHint() const
{
	TArray<IHandInteractor*> Interactors { GetGrabber(), GetPicker(), GetInteractor() };

	for (const auto* Interactor : Interactors)
	{
		if (const auto& HintMessage = ConstructHintFor(Interactor); !HintMessage.IsEmpty())
		{
			return HintMessage;
		}
	}

	return {};
}

FText UHintProducer::ConstructHintFor(const IHandInteractor* Interactor) const
{
	if (Interactor)
	{
		return Interactor->ConstructHint();
	}
	return {};
}

UGrabber* UHintProducer::GetGrabber() const
{
	return GetOwner()->FindComponentByClass<UGrabber>();
}

UInteractor* UHintProducer::GetInteractor() const
{
	return GetOwner()->FindComponentByClass<UInteractor>();
}

UPicker* UHintProducer::GetPicker() const
{
	return GetOwner()->FindComponentByClass<UPicker>();
}

