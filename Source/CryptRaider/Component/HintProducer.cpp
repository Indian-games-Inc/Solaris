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
	if (const auto* Grabber = GetGrabber(); IsValid(Grabber))
	{
		if (const auto& HintMessage = Grabber->ConstructHintMessage(); !HintMessage.IsEmpty())
		{
			return HintMessage;	
		}
	}
	if (const auto* Picker = GetPicker(); IsValid(Picker))
	{
		if (const auto& HintMessage = Picker->ConstructHintMessage(); !HintMessage.IsEmpty())
		{
			return HintMessage;	
		}
	}
	if (const auto* Interactor = GetInteractor(); IsValid(Interactor))
	{
		if (const auto& HintMessage = Interactor->ConstructHintMessage(); !HintMessage.IsEmpty())
		{
			return HintMessage;	
		}
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

