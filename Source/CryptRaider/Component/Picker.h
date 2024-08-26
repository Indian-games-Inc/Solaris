// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseHandInteractor.h"
#include "Misc/Optional.h"

#include "Picker.generated.h"

class UInventory;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FItemPicked, const struct FInventoryItemWrapper&, Item);


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRYPTRAIDER_API UPicker : public UBaseHandInteractor
{
	GENERATED_BODY()

public:
	virtual void Interact() override;
	virtual FText ConstructHint() const override;
	
private:
	TOptional<FInventoryItemWrapper> PickItem();

public:
	FItemPicked OnItemPicked;
};
