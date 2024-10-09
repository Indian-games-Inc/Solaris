#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/InventoryItemWrapper.h"
#include "Inventory.generated.h"

struct FInventoryItemWrapper;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRYPTRAIDER_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void InitItemsArray();
	
	UFUNCTION(BlueprintCallable)
	void AddItem(const FInventoryItemWrapper& Item);

	UFUNCTION(BlueprintCallable)
	TArray<FInventoryItemWrapper> GetItems() const;

	UFUNCTION(BlueprintCallable)
	int GetRows() const;

	UFUNCTION(BlueprintCallable)
	int GetColumns() const;

	UFUNCTION(BlueprintCallable)
	int GetItemsCount() const;

	UFUNCTION(BlueprintCallable)
	int ToFlatIndex(int I, int J);

	UFUNCTION(BlueprintCallable)
	FInventoryItemWrapper GetItemOnIndex(int Index) const;
	
	UFUNCTION(BlueprintCallable)
	void SwapItems(int OldIndex, int NewIndex);

	UFUNCTION(BlueprintCallable)
	FInventoryItemWrapper RemoveItem(int Index);

	UFUNCTION(BlueprintCallable)
	bool IsFull() const;
	bool HasItem(const FString& ItemId) const;

private:
	UPROPERTY(EditAnywhere)
	int Rows = 5;
	UPROPERTY(EditAnywhere)
	int Columns = 3;
	UPROPERTY(EditAnywhere)
	int ItemsCount = 0;
	UPROPERTY(EditAnywhere)
	TArray<FInventoryItemWrapper> Items = {};
};
