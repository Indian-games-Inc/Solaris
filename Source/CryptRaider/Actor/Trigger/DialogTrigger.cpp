// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogTrigger.h"

#include "Components/BoxComponent.h"

// Sets default values
ADialogTrigger::ADialogTrigger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	SetRootComponent(Root);

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(FName("Trigger Box"));
	TriggerBox->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ADialogTrigger::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADialogTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
