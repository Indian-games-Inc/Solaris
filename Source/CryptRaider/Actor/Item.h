// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseInteractible.h"
#include "../Data/ItemData.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

struct FItemData;

UCLASS()
class CRYPTRAIDER_API AItem : public ABaseInteractible
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AItem();

public:
	virtual void Interact() override {};

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	FItemData Pick();

private:
	// all item specs
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FItemData ItemData;
};
