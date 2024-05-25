// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogTrigger.h"

#include "Components/BoxComponent.h"
#include "CryptRaider/Player/BaseCharacter.h"


// Sets default values
ADialogTrigger::ADialogTrigger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	SetRootComponent(Root);

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(FName("Trigger Box"));
	TriggerBox->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ADialogTrigger::BeginPlay()
{
	Super::BeginPlay();

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ADialogTrigger::OnTriggerBeginOverlap);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ADialogTrigger::OnTriggerEndOverlap);
}

// Called every frame
void ADialogTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADialogTrigger::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent,
                                           AActor* OtherActor,
                                           UPrimitiveComponent* OtherComp,
                                           int32 OtherBodyIndex,
                                           bool bFromSweep,
                                           const FHitResult& SweepResult)
{
	// if (auto* Player = Cast<ABaseCharacter>(OtherActor))
	// {
	UE_LOG(LogTemp, Warning, TEXT("Oops you are dead"));
	// }
}

void ADialogTrigger::OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent,
                                         AActor* OtherActor,
                                         UPrimitiveComponent* OtherComp,
                                         int32 OtherBodyIndex)
{
	//
}
