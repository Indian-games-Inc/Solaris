// Fill out your copyright notice in the Description page of Project Settings.


#include "SkeletalItem.h"

ASkeletalItem::ASkeletalItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ASkeletalItem::CleanMesh()
{
	Mesh->ConditionalBeginDestroy();
	Mesh->DestroyComponent();
	Mesh = nullptr;
}

void ASkeletalItem::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	//TODO: overcomplicated
	if (MeshClass)
	{
		if (!Mesh)
		{
			UE_LOG(LogTemp, Warning, TEXT("Mesh class set"));
			Mesh = NewObject<UMeshComponent>(this, MeshClass, "Mesh");
		}
		else
		{
			if (MeshClass != Mesh->GetClass())
			{
				CleanMesh();
				Mesh = NewObject<UMeshComponent>(this, MeshClass, "Mesh");
				UE_LOG(LogTemp, Warning, TEXT("Mesh class replaced"));
			}
		}
	}
	else
	{
		if (Mesh)
		{
			CleanMesh();
			UE_LOG(LogTemp, Warning, TEXT("Mesh cleared"));
		}
	}
}
