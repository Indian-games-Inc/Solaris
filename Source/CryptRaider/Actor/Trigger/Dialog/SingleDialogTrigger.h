// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogTrigger.h"
#include "GameFramework/Actor.h"
#include "SingleDialogTrigger.generated.h"

/*
 * Plays subs only once
 */
UCLASS()
class CRYPTRAIDER_API ASingleDialogTrigger : public ADialogTrigger
{
	GENERATED_BODY()

protected:
	virtual FDataTableRowHandle PickDialog() override;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Dialog Trigger")
	FDataTableRowHandle DialogRow;
};
