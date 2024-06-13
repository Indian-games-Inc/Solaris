// Fill out your copyright notice in the Description page of Project Settings.


#include "OverTimeDamageTrigger.h"
#include "Kismet/GameplayStatics.h"

#include "Components/BoxComponent.h"
#include "CryptRaider/Player/BaseCharacter.h"


// Sets default values
AOverTimeDamageTrigger::AOverTimeDamageTrigger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AOverTimeDamageTrigger::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AOverTimeDamageTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AOverTimeDamageTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
                                                   AActor* OtherActor,
                                                   UPrimitiveComponent* OtherComp,
                                                   int32 OtherBodyIndex,
                                                   bool bFromSweep,
                                                   const FHitResult& SweepResult)
{
	if (auto* Player = Cast<ABaseCharacter>(OtherActor))
	{
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "DealDamageTo", Player);
	
		GetWorldTimerManager().SetTimer(DamageTimer, Delegate, DamageDelay, true, DamageDelay);
	}
}

void AOverTimeDamageTrigger::OnEndOverlap(UPrimitiveComponent* OverlappedComponent,
                                                 AActor* OtherActor,
                                                 UPrimitiveComponent* OtherComp,
                                                 int32 OtherBodyIndex)
{
	GetWorldTimerManager().ClearTimer(DamageTimer);

	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}

void AOverTimeDamageTrigger::DealDamageTo(AActor* OtherActor)
{
	UGameplayStatics::ApplyDamage(OtherActor, Damage, nullptr, this, UDamageType::StaticClass());
}
