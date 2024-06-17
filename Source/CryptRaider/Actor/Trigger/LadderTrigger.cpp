// Fill out your copyright notice in the Description page of Project Settings.


#include "LadderTrigger.h"

#include "CryptRaider/Player/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"


// Sets default values
ALadderTrigger::ALadderTrigger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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

// Called when the game starts or when spawned
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
	
	if (auto* Character = Cast<ABaseCharacter>(OtherActor))
	{
		if (IsGlued)
		{
			Character->SetOnLadder(true);
		}
		else
		{
			Character->SetOnLadder(false);
			Character->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
		}
	}
}

void ALadderTrigger::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
	if (auto* Character = Cast<ABaseCharacter>(OtherActor))
	{
		Character->SetOnLadder(false);
		Character->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	}
}

// Called every frame
void ALadderTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
