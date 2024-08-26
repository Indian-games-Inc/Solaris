// Fill out your copyright notice in the Description page of Project Settings.


#include "HintProducer.h"

#include "Grabber.h"
#include "Interactor.h"
#include "Picker.h"


// Sets default values for this component's properties
UHintProducer::UHintProducer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called every frame
void UHintProducer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (const auto& HintMessage = ConstructHint(); !HintMessage.IsEmpty())
	{
		OnHintUpdated.Broadcast(HintMessage);
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

