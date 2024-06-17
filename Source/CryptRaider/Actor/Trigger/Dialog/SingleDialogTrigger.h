// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogTrigger.h"
#include "GameFramework/Actor.h"
#include "SingleDialogTrigger.generated.h"

/*
 * Plays DialogRow only once
 */
UCLASS()
class CRYPTRAIDER_API ASingleDialogTrigger : public ADialogTrigger
{
	GENERATED_BODY()

protected:
	virtual void SwitchTriggerState() override;
	virtual FDataTableRowHandle PickDialog() override;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Dialog Trigger")
	FDataTableRowHandle DialogRow;
};
