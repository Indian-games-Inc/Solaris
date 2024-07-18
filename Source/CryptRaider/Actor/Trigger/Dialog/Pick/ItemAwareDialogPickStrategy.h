// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseDialogPickStrategy.h"
#include "ItemAwareDialogPickStrategy.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRYPTRAIDER_API UItemAwareDialogPickStrategy : public UBaseDialogPickStrategy
{
	GENERATED_BODY()

public:
	virtual FDataTableRowHandle GetDialog() override;

private:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
	TArray<FDataTableRowHandle> PreDialogList;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
	TArray<FDataTableRowHandle> PostDialogList;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
	FString ItemId;
};
