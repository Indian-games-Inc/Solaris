// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CryptRaider/Interface/Interactable.h"
#include "GameFramework/Actor.h"
#include "PrototypeSkeletalItem.generated.h"

UCLASS()
class CRYPTRAIDER_API APrototypeSkeletalItem : public AActor
{
	GENERATED_BODY()

public:
	APrototypeSkeletalItem();
	void CleanMesh();
	virtual void OnConstruction(const FTransform& Transform) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mesh",
		meta=(AllowPrivateAccess = "true", AllowedClasses = "/Script/Engine.StaticMeshComponent,/Script/Engine.SkeletalMeshComponent"))
	TSubclassOf<UMeshComponent> MeshClass;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Mesh", meta=(AllowPrivateAccess = "true",
		AllowedClasses = "/Script/Engine.StaticMeshComponent,/Script/Engine.SkeletalMeshComponent"))
	TObjectPtr<UMeshComponent> Mesh;
};
