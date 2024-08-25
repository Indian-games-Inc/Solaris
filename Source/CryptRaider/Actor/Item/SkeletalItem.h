// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SkeletalItem.generated.h"

UCLASS()
class CRYPTRAIDER_API ASkeletalItem : public AActor
{
	GENERATED_BODY()

public:
	ASkeletalItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Body;
private:
	USceneComponent* Root = nullptr;

};
