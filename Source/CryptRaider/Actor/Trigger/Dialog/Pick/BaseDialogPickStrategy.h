// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CryptRaider/Interface/DialogPickStrategy.h"
#include "BaseDialogPickStrategy.generated.h"


UCLASS(HideDropdown, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRYPTRAIDER_API UBaseDialogPickStrategy : public UActorComponent, public IDialogPickStrategy
{
	GENERATED_BODY()

public:
	virtual FDataTableRowHandle GetDialog() override;
};
