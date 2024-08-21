// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MonsterStage.generated.h"

UENUM(BlueprintType)
enum class EMonsterStage : uint8
{
	Friendly      UMETA(DisplayName = "Friendly"),
	Neutral       UMETA(DisplayName = "Neutral"),
	Aggressive    UMETA(DisplayName = "Aggressive"),
	Death		  UMETA(DisplayName = "Death"),
	None		  UMETA(DisplayName = "None"),
};
