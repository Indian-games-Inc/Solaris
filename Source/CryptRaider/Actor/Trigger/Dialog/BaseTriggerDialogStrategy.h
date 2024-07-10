// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CryptRaider/Interface/TriggerDialogStrategy.h"
#include "BaseTriggerDialogStrategy.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRYPTRAIDER_API UBaseTriggerDialogStrategy : public UActorComponent, public ITriggerDialogStrategy
{
	GENERATED_BODY()

public:
	virtual FDataTableRowHandle GetDialog() override;

// private:
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialogs", meta=(AllowPrivateAccess="true"))
// 	TArray<FDataTableRowHandle> Dialogs;
};
