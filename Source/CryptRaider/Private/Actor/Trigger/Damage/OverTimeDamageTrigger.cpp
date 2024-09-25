#include "Actor/Trigger/Damage/OverTimeDamageTrigger.h"
#include "Kismet/GameplayStatics.h"
#include "Player/BaseCharacter.h"


AOverTimeDamageTrigger::AOverTimeDamageTrigger()
{
	PrimaryActorTick.bCanEverTick = true;
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
