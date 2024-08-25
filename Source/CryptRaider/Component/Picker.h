// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Misc/Optional.h"
#include "Picker.generated.h"

class UInventory;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPickerHintUpdate, const FText&, Hints);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRYPTRAIDER_API UPicker : public UActorComponent
{
	GENERATED_BODY()

public:
	UPicker();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	TOptional<struct FInventoryItemWrapper> PickItem(const FHitResult& HitResult);

private:
	class UHand* GetHand() const;
	class ABasePlayerController* GetController() const;

	FText ConstructHintMessage() const;

public:
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FPickerHintUpdate OnHintUpdated;
};
