// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CooldownDialogTrigger.h"
#include "RandomCooldownDialogTrigger.generated.h"

UCLASS()
class CRYPTRAIDER_API ARandomCooldownDialogTrigger : public ADialogTrigger
{
	GENERATED_BODY()

public:
	virtual FDataTableRowHandle PickDialog() override;

protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Dialog Trigger")
	float PlayBackCooldown;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Dialog Trigger")
	TArray<FDataTableRowHandle> DialogRowList = {};
};
