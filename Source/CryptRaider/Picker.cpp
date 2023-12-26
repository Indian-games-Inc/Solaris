// Fill out your copyright notice in the Description page of Project Settings.


#include "Picker.h"
#include "Inventory.h"
#include "Item.h"

// Sets default values for this component's properties
UPicker::UPicker()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPicker::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UPicker::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPicker::SetInventory(UInventory* _Inventory)
{
	this->Inventory = _Inventory;
}

void UPicker::PickItem()
{
	FHitResult HitResult;

	FVector Start = GetComponentLocation() + GetForwardVector();
	FVector End = Start + GetForwardVector() * 100;

	DrawDebugLine(GetWorld(), Start, End, FColor::Cyan);

	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);

	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult, Start, End,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		Sphere
	);


	//TODO: 
	//AActor should be extended with 
	//add all nessessary fileds to it

	if (HasHit)
	{
		auto* Item = Cast<AItem>(HitResult.GetActor());
		if (Item)
		{
			// HitResult.GetActor()
			auto data = Item->GetData();
			UE_LOG(LogTemp, Warning, TEXT("%s"), *data.Name);
			UE_LOG(LogTemp, Warning, TEXT("%s"), *data.Description);
			UE_LOG(LogTemp, Warning, TEXT("%f"), data.Weight);

			this->Inventory->AddItem(Item->GetData());
		}
	}
}
