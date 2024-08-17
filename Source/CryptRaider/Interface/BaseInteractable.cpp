// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseInteractable.h"

#include "GameFramework/Character.h"


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
	OnTakeAnyDamage.AddUniqueDynamic(this, &ABaseInteractable::OnDamage);
}

void ABaseInteractable::PlayNoise()
{
	MakeNoise(0.5F, GetWorld()->GetFirstPlayerController()->GetCharacter()->GetInstigator(), GetActorLocation());
}

// Called every frame
void ABaseInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetVelocity().Length() > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("ABaseInteractable, %s"), *this->GetName());
		PlayNoise();
	}
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

void ABaseInteractable::OnDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                 AController* InstigatedBy, AActor* DamageCauser)
{
	Destroy();
}
