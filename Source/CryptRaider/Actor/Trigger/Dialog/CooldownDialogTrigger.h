// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogTrigger.h"
#include "SingleDialogTrigger.h"
#include "GameFramework/Actor.h"
#include "CooldownDialogTrigger.generated.h"

UCLASS()
class CRYPTRAIDER_API ACooldownDialogTrigger : public ADialogTrigger
{
	GENERATED_BODY()

protected:
	virtual void SwitchTriggerState() override;
	virtual FDataTableRowHandle PickDialog() override;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Dialog Trigger")
	FDataTableRowHandle DialogRow;
	
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Dialog Trigger")
	float PlayBackCooldown;

private:
	// Timer handle for managing delay
	FTimerHandle DelayTimerHandle;
};
