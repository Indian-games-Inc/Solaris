// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseInteractable.h"


// Sets default values
ABaseInteractable::ABaseInteractable()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABaseInteractable::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ABaseInteractable::IsActive() const
{
	return true;
}

void ABaseInteractable::Interact()
{
	// Should be blank
}

FString ABaseInteractable::HintMessage() const
{
	return "Interact";
}

void ABaseInteractable::DisablePhysics() const
{
	Body->SetSimulatePhysics(false);
	Body->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Body->OnActorEnableCollisionChanged();
}

void ABaseInteractable::EnablePhysics() const
{
	Body->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Body->OnActorEnableCollisionChanged();
}
