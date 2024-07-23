// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CryptRaider/Interface/DialogStateStrategy.h"
#include "BaseTriggerStateStrategy.generated.h"


UCLASS(HideDropdown, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRYPTRAIDER_API UBaseTriggerStateStrategy : public UActorComponent, public IDialogStateStrategy
{
	GENERATED_BODY()

public:
	virtual bool IsActive() override;
	virtual void OnTrigger() override;
};
