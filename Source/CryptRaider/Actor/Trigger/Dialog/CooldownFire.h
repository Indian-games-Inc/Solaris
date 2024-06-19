// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cooldownable.h"
#include "GameFramework/Actor.h"
#include "CooldownFire.generated.h"

UCLASS()
class CRYPTRAIDER_API ACooldownFire final : public ACooldownable
{
	GENERATED_BODY()

protected:
	virtual FDataTableRowHandle PickDialog() override;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Dialog Trigger")
	FDataTableRowHandle DialogRow;
	
private:
	FTimerHandle DelayTimerHandle;
};
