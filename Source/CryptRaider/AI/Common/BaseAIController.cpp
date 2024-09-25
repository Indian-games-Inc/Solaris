// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAIController.h"

#include "BaseAICharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "CryptRaider/Actor/Destructible/Projectile.h"
#include "CryptRaider/Damage/Type/StunDamageType.h"

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
		AICharacter->OnTakeStunDamage.AddDynamic(this, &ABaseAIController::OnActorTakeStunDamage);
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

void ABaseAIController::OnActorTakeStunDamage(AActor* DamagedActor, float Damage, const FHitResult& Hit,
                                              AController* InstigatedBy, const UDamageType* DamageType, AActor* DamageCauser)
{
	if (IsValid(Cast<AProjectile>(DamageCauser)) && IsValid(Cast<UStunDamageType>(DamageType)))
	{
		BlackboardComponent->SetValueAsVector(HitLocationKeyName, Hit.Location);

		const FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetCharacter()->GetActorLocation();
		BlackboardComponent->SetValueAsVector(PlayerLocationKeyName, PlayerLocation);
	}
}