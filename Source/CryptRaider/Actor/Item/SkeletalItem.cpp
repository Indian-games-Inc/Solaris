// Fill out your copyright notice in the Description page of Project Settings.


#include "SkeletalItem.h"

// Sets default values
ASkeletalItem::ASkeletalItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ASkeletalItem::Charge()
{
}

// Called when the game starts or when spawned
void ASkeletalItem::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASkeletalItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
