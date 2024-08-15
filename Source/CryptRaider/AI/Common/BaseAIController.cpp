// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAIController.h"

#include "BaseAICharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "CryptRaider/Actor/Destructible/Projectile.h"
#include "GameFramework/GameSession.h"

// Sets default values
ABaseAIController::ABaseAIController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Tree Component"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));
}

// Called when the game starts or when spawned
void ABaseAIController::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(BehaviorTree.Get()))
	{
		RunBehaviorTree(BehaviorTree);
		BehaviorTreeComponent->StartTree(*BehaviorTree.Get());
	}

	if (auto* AICharacter = Cast<ABaseAICharacter>(GetCharacter()); IsValid(AICharacter))
	{
		AICharacter->OnPlayerOnSightUpdate.AddDynamic(this, &ABaseAIController::OnPLayerOnSight);
		AICharacter->OnActorHit.AddDynamic(this, &ABaseAIController::OnActorHit);
	}
}

void ABaseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

// Called every frame
void ABaseAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsValid(Blackboard) && IsValid(BehaviorTree))
	{
		Blackboard->InitializeBlackboard(*BehaviorTree->BlackboardAsset.Get());
	}
}

void ABaseAIController::OnPLayerOnSight(const bool IsPlayerOnSight, const FVector& PlayerLocation)
{
	BlackboardComponent->SetValueAsBool(IsPursuingPlayerKeyName, true);
	
	BlackboardComponent->SetValueAsBool(IsPlayerOnSightKeyName, IsPlayerOnSight);
	BlackboardComponent->SetValueAsVector(PlayerLocationKeyName, PlayerLocation);
}

void ABaseAIController::OnActorHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (const auto* Projectile = Cast<AProjectile>(OtherActor); IsValid(Projectile) && Projectile->IsCharged())
	{
		BlackboardComponent->SetValueAsVector(HitLocationKeyName, Hit.Location);

		const FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetCharacter()->GetActorLocation();
		BlackboardComponent->SetValueAsVector(PlayerLocationKeyName, PlayerLocation);
	}
}
