// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CryptRaider/Interface/TriggerStateStrategy.h"
#include "BaseTriggerStateStrategy.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRYPTRAIDER_API UBaseTriggerStateStrategy : public UActorComponent, public ITriggerStateStrategy
{
	GENERATED_BODY()

public:
	virtual bool IsActive() override;
	virtual void OnTrigger() override;
};
