#include "Actor/Trigger/LadderTrigger.h"

#include "Player/BaseCharacter.h"
#include "Components/BoxComponent.h"



ALadderTrigger::ALadderTrigger()
{
	PrimaryActorTick.bCanEverTick = true;

	LadderBox = CreateDefaultSubobject<UBoxComponent>(FName("Ladder Box"));
	LadderBox->ShapeColor = FColor(0, 0, 255);
	LadderBox->SetupAttachment(RootComponent);

	FCollisionResponseContainer LadderBoxCollisionResponses;
	LadderBoxCollisionResponses.SetResponse(ECC_WorldDynamic, ECR_Ignore);
	LadderBoxCollisionResponses.SetResponse(ECC_Pawn, ECR_Overlap);
	LadderBox->SetCollisionResponseToChannels(LadderBoxCollisionResponses);
}

void ALadderTrigger::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	LadderBox->SetVisibility(IsDebug);
	LadderBox->SetHiddenInGame(!IsDebug);
}


void ALadderTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	// Register overlap events for MeshComponent
	LadderBox->OnComponentBeginOverlap.AddDynamic(this, &ALadderTrigger::OnBeginOverlap);
	LadderBox->OnComponentEndOverlap.AddDynamic(this, &ALadderTrigger::OnEndOverlap);
}

void ALadderTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                    const FHitResult& SweepResult)
{
	Super::OnBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (auto* Movement = OtherActor->FindComponentByClass<UMovement>())
	{
		Movement->SetOnLadder(IsGlued);
	}
}

void ALadderTrigger::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);

	if (auto* Movement = OtherActor->FindComponentByClass<UMovement>())
	{
		Movement->SetOnLadder(false);
	}
}
