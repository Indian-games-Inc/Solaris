// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HintProducer.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHintUpdated, const FText&, Hints);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRYPTRAIDER_API UHintProducer : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHintProducer();

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

private:
	FText ConstructHint() const;
	FText ConstructHintFor(const class IHandInteractor* Interactor) const;

	class UGrabber* GetGrabber() const;
	class UInteractor* GetInteractor() const;
	class UPicker* GetPicker() const;

public: // Events
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FHintUpdated OnHintUpdated;
};
