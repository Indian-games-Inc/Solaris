// Fill out your copyright notice in the Description page of Project Settings.

#include "Item.h"
#include "../Data/ItemData.h"

// Sets default values
AItem::AItem()
{
	ItemData.Name = GetName();
	ItemData.ID = GetName();
	ItemData.Model = DuplicateObject<UStaticMesh>(Body->GetStaticMesh(), nullptr);
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
}

FItemData AItem::Pick()
{
	Destroy();
	return this->ItemData;
}

void AItem::Interact()
{
	Super::Interact();
}

FString AItem::HintMessage() const
{
	return "Pick up";
}
