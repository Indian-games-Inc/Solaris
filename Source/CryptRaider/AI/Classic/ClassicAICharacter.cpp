// Fill out your copyright notice in the Description page of Project Settings.


#include "ClassicAICharacter.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "CryptRaider/Player/BaseCharacter.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

// Sets default values
AClassicAICharacter::AClassicAICharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("AI Perception");
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AClassicAICharacter::OnTargetPerceptionUpdated);
}

// Called when the game starts or when spawned
void AClassicAICharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AClassicAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AClassicAICharacter::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (const auto* Player = Cast<ABaseCharacter>(Actor); !IsValid(Player))
	{
		UE_LOG(LogTemp, Warning, TEXT("Detected non-player Actor"));
		return;
	}
	
	if (auto* AIController = Cast<AAIController>(GetController()); IsValid(AIController))
	{
		if (auto* BlackboardComponent = AIController->GetBlackboardComponent(); IsValid(BlackboardComponent))
		{
			if (Stimulus.WasSuccessfullySensed())
			{
				BlackboardComponent->SetValueAsBool(IsPlayerOnSightName, true);
				BlackboardComponent->SetValueAsBool(IsPursuingPlayerName, true);
			}
			else
			{
				BlackboardComponent->SetValueAsBool(IsPlayerOnSightName, false);
			}
		}
	}
}
