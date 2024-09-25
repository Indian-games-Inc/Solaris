#include "Actor/Trigger/NoiseTrigger.h"

void ANoiseTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	MakeNoise(Loudness, OtherActor->GetInstigator(), OtherActor->GetActorLocation());
}
