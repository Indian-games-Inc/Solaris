#include "Actor/Trigger/BaseTrigger.h"

#include "Components/BoxComponent.h"


ABaseTrigger::ABaseTrigger()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	SetRootComponent(Root);

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(FName("Trigger Box"));
	TriggerBox->SetupAttachment(RootComponent);
}

void ABaseTrigger::BeginPlay()
{
	Super::BeginPlay();

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ABaseTrigger::OnBeginOverlap);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ABaseTrigger::OnEndOverlap);
}

void ABaseTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                  const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Display, TEXT("Begin overlap with Actor: %s"), *OtherActor->GetName());
}

void ABaseTrigger::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Display, TEXT("End overlap with Actor: %s"), *OtherActor->GetName());
}