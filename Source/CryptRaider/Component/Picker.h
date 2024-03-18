// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Misc/Optional.h"
#include "Picker.generated.h"

class UInventory;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRYPTRAIDER_API UPicker : public USceneComponent
{
	GENERATED_BODY()

public:
	TOptional<struct FInventoryItemWrapper> PickItem(const FHitResult& HitResult);
};
