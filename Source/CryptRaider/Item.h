// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
// #include "FItemData.h"
#include "ItemData.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

struct FItemData;

UCLASS()
class CRYPTRAIDER_API AItem : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FItemData GetData();

private:
	// //all item specs
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FItemData ItemData;
};
