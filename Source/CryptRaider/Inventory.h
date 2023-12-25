// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory.generated.h"

struct FItemData;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRYPTRAIDER_API UInventory : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	// Add to inventory
	UFUNCTION(BlueprintCallable)
	void AddItem(const FItemData& Item);

private:
	UPROPERTY(EditAnywhere)
	int InventorySize = 10;

	UPROPERTY(EditAnywhere)
	TArray<FItemData> InventoryItems = {};
};
