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
	UHintProducer();

public:
    virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

private:
	FText ConstructHint() const;
	FText ConstructHintFor(const class IHandInteractor* Interactor) const;

	class UGrabber* GetGrabber() const;
	class UInteractor* GetInteractor() const;
	class UPicker* GetPicker() const;

public:
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FHintUpdated OnHintUpdated;
};
