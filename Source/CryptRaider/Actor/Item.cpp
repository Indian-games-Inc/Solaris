// Fill out your copyright notice in the Description page of Project Settings.

#include "Item.h"
#include "../Data/ItemData.h"

// Sets default values
AItem::AItem()
{
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	this->ItemData.Model = DuplicateObject<UStaticMesh>(Body->GetStaticMesh(), nullptr);
}

FItemData AItem::Pick()
{
	Destroy();
	return this->ItemData;
}
