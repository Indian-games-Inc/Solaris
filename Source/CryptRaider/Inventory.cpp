// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory.h"
#include "ItemData.h"

// Sets default values for this component's properties
UInventory::UInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
	this->InventoryItems;
}


// Called when the game starts
void UInventory::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// Add item to inventory
void UInventory::AddItem(const FItemData& Item)
{
	this->InventoryItems.Add(Item);
}

TArray<FItemData> UInventory::GetInventoryItems()
{
	return this->InventoryItems;
}
