// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseAIController.generated.h"

UCLASS()
class CRYPTRAIDER_API ABaseAIController : public AAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseAIController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnPLayerOnSight(const bool IsPlayerOnSight, const FVector& PlayerLocation);

	UFUNCTION()
	void OnActorTakeStunDamage(AActor* DamagedActor, float Damage, const FHitResult& Hit, AController* InstigatedBy, const UDamageType* DamageType, AActor* DamageCauser);

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="AI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UBehaviorTreeComponent> BehaviorTreeComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBlackboardComponent> BlackboardComponent;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI|Blackboard", meta = (AllowPrivateAccess = "true"))
	FName IsPlayerOnSightKeyName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI|Blackboard", meta = (AllowPrivateAccess = "true"))
	FName IsPursuingPlayerKeyName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI|Blackboard", meta = (AllowPrivateAccess = "true"))
	FName PlayerLocationKeyName;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI|Blackboard", meta = (AllowPrivateAccess = "true"))
	FName HitLocationKeyName;
};
