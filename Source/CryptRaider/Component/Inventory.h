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
	UFUNCTION(BlueprintCallable)
	void InitItemsArray();
	
	UFUNCTION(BlueprintCallable)
	void AddItem(const FItemData& Item);

	UFUNCTION(BlueprintCallable)
	TArray<FItemData> GetInventoryItems();

	UFUNCTION(BlueprintCallable)
	int GetRows();

	UFUNCTION(BlueprintCallable)
	int GetColumns();

	UFUNCTION(BlueprintCallable)
	int GetItemsCount();

	UFUNCTION(BlueprintCallable)
	int ToFlatIndex(int I, int J);

	UFUNCTION(BlueprintCallable)
	FItemData GetItemOnIndex(int index);
	
	UFUNCTION(BlueprintCallable)
	void SwapItems(int OldIndex, int NewIndex);

private:
	UPROPERTY(EditAnywhere)
	int Rows = 5;
	UPROPERTY(EditAnywhere)
	int Columns = 3;
	UPROPERTY(EditAnywhere)
	int ItemsCount = 0;
	UPROPERTY(EditAnywhere)
	TArray<FItemData> Items = {};
};
