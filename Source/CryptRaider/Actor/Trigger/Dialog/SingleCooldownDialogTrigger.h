// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CooldownDialogTrigger.h"
#include "GameFramework/Actor.h"
#include "SingleCooldownDialogTrigger.generated.h"

UCLASS()
class CRYPTRAIDER_API ASingleCooldownDialogTrigger final : public ACooldownDialogTrigger
{
	GENERATED_BODY()

protected:
	// virtual FDataTableRowHandle PickDialog() override;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Dialog Trigger")
	FDataTableRowHandle DialogRow;
};
