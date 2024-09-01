// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CryptRaider/Interface/Interactable.h"
#include "GameFramework/Actor.h"
#include "SkeletalItem.generated.h"

UCLASS()
class CRYPTRAIDER_API ASkeletalItem : public AActor
{
	GENERATED_BODY()

public:
	ASkeletalItem();
	virtual void OnConstruction(const FTransform& Transform) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mesh", meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UMeshComponent> MeshClass;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Mesh", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UMeshComponent> Mesh;

};
