// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseTriggerDialogStrategy.h"
#include "SingleDialogStrategy.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRYPTRAIDER_API USingleDialogStrategy : public UBaseTriggerDialogStrategy
{
	GENERATED_BODY()

public:
	virtual FDataTableRowHandle GetDialog() override;

private:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Dialog", meta=(AllowPrivateAccess="true"))
	FDataTableRowHandle	Dialog;
};
