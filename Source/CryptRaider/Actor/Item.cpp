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
	ItemData.Model = DuplicateObject<UStaticMesh>(Body->GetStaticMesh(), nullptr);
	Body->OnComponentHit.AddDynamic(this, &AItem::OnComponentHit);
}

FItemData AItem::Pick()
{
	Destroy();
	return this->ItemData;
}

void AItem::DisablePhysics() const
{
	Body->SetSimulatePhysics(false);
	Body->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AItem::EnablePhysics() const
{
	Body->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Body->OnActorEnableCollisionChanged();
}
