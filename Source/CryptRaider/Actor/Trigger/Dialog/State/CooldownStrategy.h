// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseTriggerStateStrategy.h"
#include "CooldownStrategy.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRYPTRAIDER_API UCooldownStrategy : public UBaseTriggerStateStrategy
{
	GENERATED_BODY()

public:
	virtual bool IsActive() override;
	virtual void OnTrigger() override;

private:
	UPROPERTY(EditInstanceOnly, meta=(AllowPrivateAccess="true"))
	float PlayBackCooldown = 5.0f;

	UPROPERTY()
	bool Active = true;

	UPROPERTY()
	FTimerHandle DelayTimerHandle;
};
