#include "Actor/Trigger/Damage/DeathTrigger.h"

#include "Damage/Type/InstantDeathDamage.h"
#include "Kismet/GameplayStatics.h"
#include "Player/BaseCharacter.h"


ADeathTrigger::ADeathTrigger()
{
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
	// Blank Implementation
}
