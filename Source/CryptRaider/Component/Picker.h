// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Picker.generated.h"

class UInventory;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRYPTRAIDER_API UPicker : public USceneComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	bool HasItemNear();

	UFUNCTION(BlueprintCallable)
	struct FInventoryItemWrapper PickItem();

private:
	bool GetPickableInReach(FHitResult& HitResult) const;

	UPROPERTY(EditAnywhere)
	float PickRadius = 100;

	UPROPERTY(EditAnywhere)
	float MaxPickDistance = 250;
	
};
