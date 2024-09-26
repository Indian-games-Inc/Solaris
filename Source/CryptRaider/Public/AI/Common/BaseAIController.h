#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseAIController.generated.h"

UCLASS()
class CRYPTRAIDER_API ABaseAIController : public AAIController
{
	GENERATED_BODY()

public:
	ABaseAIController();

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

public:
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

