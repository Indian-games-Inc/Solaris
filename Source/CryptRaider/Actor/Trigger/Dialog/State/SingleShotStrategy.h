// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseTriggerStateStrategy.h"
#include "Components/ActorComponent.h"
#include "CryptRaider/Interface/DialogStateStrategy.h"
#include "SingleShotStrategy.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRYPTRAIDER_API USingleShotStrategy : public UBaseTriggerStateStrategy
{
	GENERATED_BODY()

public:
	virtual bool IsActive() override;
	virtual void OnTrigger() override;

private:
	UPROPERTY()
	bool Active = true;
};
