// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cooldownable.h"
#include "CooldownFire.h"
#include "RandomCooldownFire.generated.h"

UCLASS()
class CRYPTRAIDER_API ARandomCooldownFire final : public ACooldownable
{
	GENERATED_BODY()

public:
	virtual FDataTableRowHandle PickDialog() override;

protected:

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Dialog Trigger")
	TArray<FDataTableRowHandle> DialogRowList = {};
};
