// Fill out your copyright notice in the Description page of Project Settings.

#include "Item.h"
#include "ItemData.h"

// Sets default values
AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	this->ItemData.Model = DuplicateObject<UStaticMesh>(Body->GetStaticMesh(), nullptr);
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FItemData AItem::Pick()
{
	Destroy();
	return this->ItemData;
}
