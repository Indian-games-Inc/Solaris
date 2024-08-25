// Fill out your copyright notice in the Description page of Project Settings.


#include "SkeletalItem.h"

ASkeletalItem::ASkeletalItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	SetRootComponent(Root);
	Body = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	Body->SetupAttachment(RootComponent);
}
