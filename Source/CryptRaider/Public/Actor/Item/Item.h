// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/ItemData.h"
#include "Interface/BaseInteractable.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

struct FItemData;

UCLASS()
class CRYPTRAIDER_API AItem : public ABaseInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	FItemData Pick();

	virtual void Interact() override;
	virtual FString HintMessage() const override;

private:
	// all item specs
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FItemData ItemData;
};
