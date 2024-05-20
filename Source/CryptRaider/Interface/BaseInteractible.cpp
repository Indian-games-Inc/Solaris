// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseInteractible.h"


// Sets default values
ABaseInteractible::ABaseInteractible()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABaseInteractible::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseInteractible::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ABaseInteractible::IsActive() const
{
	return true;
}

void ABaseInteractible::Interact()
{
	// Should be blank
}

FString ABaseInteractible::HintMessage() const
{
	return "Interact";
}

void ABaseInteractible::DisablePhysics() const
{
	Body->SetSimulatePhysics(false);
	Body->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABaseInteractible::EnablePhysics() const
{
	Body->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Body->OnActorEnableCollisionChanged();
}
