// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Misc/Optional.h"
#include "Picker.generated.h"

class UInventory;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FItemPicked, const struct FInventoryItemWrapper&, Item);


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRYPTRAIDER_API UPicker : public UActorComponent
{
	GENERATED_BODY()

public:
	UPicker();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable)
	void Interact();

	UFUNCTION(BlueprintCallable)
	FText ConstructHintMessage() const;
	
private:
	TOptional<FInventoryItemWrapper> PickItem();

	class UHand* GetHand() const;
	class ABasePlayerController* GetController() const;

public:
	FItemPicked OnItemPicked;
};
