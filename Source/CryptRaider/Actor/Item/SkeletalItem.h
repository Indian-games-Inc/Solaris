// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CryptRaider/Interface/SkeletalMeshInteractable.h"
#include "SkeletalItem.generated.h"

UCLASS()
class CRYPTRAIDER_API ASkeletalItem : public ASkeletalMeshInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASkeletalItem();
	virtual void Charge();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
