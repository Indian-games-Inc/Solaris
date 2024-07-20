// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseDialogPickStrategy.h"
#include "ItemAwareDialogPickStrategy.h"
#include "GrabberAwareDialogPickStrategy.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRYPTRAIDER_API UGrabberAwareDialogPickStrategy : public UItemAwareDialogPickStrategy
{
	GENERATED_BODY()

public:
	virtual FDataTableRowHandle GetDialog() override;
};
