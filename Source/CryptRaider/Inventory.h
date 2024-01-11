// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory.generated.h"

struct FItemData;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRYPTRAIDER_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:

	// Add to inventory
	UFUNCTION(BlueprintCallable)
	void AddItem(const FItemData& Item);

	UFUNCTION(BlueprintCallable)
	TArray<FItemData> GetInventoryItems();

private:
	UPROPERTY(EditAnywhere)
	int InventorySize = 10;

	UPROPERTY(EditAnywhere)
	TArray<FItemData> InventoryItems = {};
};
