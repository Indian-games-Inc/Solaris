// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSprite.h"
#include "ItemData.generated.h"

/**
 * Structure for item data
 */
USTRUCT(BlueprintType)
struct CRYPTRAIDER_API FItemData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Weight = 0.0F;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMeshComponent* Model;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperSprite* Icon;
};
