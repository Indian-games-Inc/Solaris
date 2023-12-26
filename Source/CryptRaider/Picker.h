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
	// Sets default values for this component's properties
	UPicker();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	FItemData PickItem();

private:
	UPROPERTY(EditAnywhere)
	float GrabRadius = 50;
};
