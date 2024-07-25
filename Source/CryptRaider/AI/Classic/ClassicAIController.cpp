// Fill out your copyright notice in the Description page of Project Settings.


#include "ClassicAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

// Sets default values
AClassicAIController::AClassicAIController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Tree Component"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));
	
}

// Called when the game starts or when spawned
void AClassicAIController::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(BehaviorTree.Get()))
	{
		RunBehaviorTree(BehaviorTree);
		BehaviorTreeComponent->StartTree(*BehaviorTree.Get());
	}
}

void AClassicAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

// Called every frame
void AClassicAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsValid(Blackboard) && IsValid(BehaviorTree))
	{
		Blackboard->InitializeBlackboard(*BehaviorTree->BlackboardAsset.Get());
	}
		
	
}

