// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory.generated.h"

struct FItemData;

/**
 * TODO:
 
 * Added Hint to items +
 * Draw hot bar in HUD +

 * Replace objects in inventory
 * Rotate object by mouse, not just static rotation

 * Have an animated model with overlapped glyphs
 * Animation for each action
 * Do cool model and design

*/

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRYPTRAIDER_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void AddItem(const FItemData& Item);

	UFUNCTION(BlueprintCallable)
	TArray<FItemData> GetInventoryItems();

	UFUNCTION(BlueprintCallable)
	float GetTotalWeight();

private:
	UPROPERTY(EditAnywhere)
	int InventorySize = 10;

	UPROPERTY(EditAnywhere)
	float InventoryWeight = 0.0f;

	UPROPERTY(EditAnywhere)
	TArray<FItemData> InventoryItems = {};
};
