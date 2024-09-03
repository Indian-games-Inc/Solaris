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
	void CleanMesh();
	virtual void OnConstruction(const FTransform& Transform) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mesh",
		meta=(AllowPrivateAccess = "true", AllowedClasses = "/Script/Engine.StaticMeshComponent,/Script/Engine.SkeletalMeshComponent"))
	TSubclassOf<UMeshComponent> MeshClass;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Mesh", meta=(AllowPrivateAccess = "true",
		AllowedClasses = "/Script/Engine.StaticMeshComponent,/Script/Engine.SkeletalMeshComponent"))
	TObjectPtr<UMeshComponent> Mesh;
};
