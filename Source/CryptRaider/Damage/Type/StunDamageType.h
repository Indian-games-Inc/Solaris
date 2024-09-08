// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "StunDamageType.generated.h"

/**
 * 
 */
UCLASS()
class CRYPTRAIDER_API UStunDamageType : public UDamageType
{
	GENERATED_BODY()

private:
	UPROPERTY()
	float DefaultStunDuration = 5.f;
};
