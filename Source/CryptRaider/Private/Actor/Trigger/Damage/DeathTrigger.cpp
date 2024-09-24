// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Trigger/Damage/DeathTrigger.h"

#include "Damage/Type/InstantDeathDamage.h"
#include "Kismet/GameplayStatics.h"
#include "Player/BaseCharacter.h"


// Sets default values
ADeathTrigger::ADeathTrigger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ADeathTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	float Damage = 1.f;
	
	if (const auto* Health = OtherActor->FindComponentByClass<UHealth>())
	{
		Damage = Health->GetMaxHealth();
	}
	UGameplayStatics::ApplyDamage(OtherActor, Damage, nullptr, this, UInstantDeathDamage::StaticClass());
}

void ADeathTrigger::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

// Called when the game starts or when spawned
void ADeathTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADeathTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

