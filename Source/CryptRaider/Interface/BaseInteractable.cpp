// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseInteractable.h"

#include "GameFramework/Character.h"


ABaseInteractable::ABaseInteractable()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABaseInteractable::BeginPlay()
{
	Super::BeginPlay();

	OnTakeAnyDamage.AddUniqueDynamic(this, &ABaseInteractable::OnDamage);

	if (auto* Body = GetBody(); IsValid(Body))
	{
		SetRootComponent(Body);
		// Bind the OnHit function
		Body->OnComponentHit.AddDynamic(this, &ABaseInteractable::OnHit);
	}
}

void ABaseInteractable::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                              FVector NormalImpulse, const FHitResult& Hit)
{
	if (GetVelocity().Length() > VelocityLimit)
	{
		UE_LOG(LogTemp, Warning, TEXT("ABaseInteractable::OnHit fired on the: %s, with velocity %f"), *this->GetName(),
		       GetVelocity().Length());
		MakeNoise(LoudnessOfOnHit, GetWorld()->GetFirstPlayerController()->GetCharacter()->GetInstigator(),
		          GetActorLocation());
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
	GetBody()->SetSimulatePhysics(false);
	GetBody()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetBody()->OnActorEnableCollisionChanged();
}

void ABaseInteractable::EnablePhysics() const
{
	GetBody()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetBody()->OnActorEnableCollisionChanged();
}

void ABaseInteractable::OnDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                 AController* InstigatedBy, AActor* DamageCauser)
{
	Destroy();
}

UMeshComponent* ABaseInteractable::GetBody() const
{
	if (auto* StaticMesh = FindComponentByClass<UStaticMeshComponent>(); IsValid(StaticMesh))
	{
		return StaticMesh;
	}
	if (auto* SkeletalMesh = FindComponentByClass<USkeletalMeshComponent>(); IsValid(SkeletalMesh))
	{
		return SkeletalMesh;
	}
	return nullptr;
}
