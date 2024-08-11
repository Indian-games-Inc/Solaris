// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseAICharacter.generated.h"

UCLASS()
class CRYPTRAIDER_API ABaseAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseAICharacter();

protected:
	virtual void BeginPlay() override;

	// Called when the game ends
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	UFUNCTION()
	virtual void OnHitEvent(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintCallable)
	void TriggerAttack();

protected:
	class UBlackboardComponent* GetBlackboardComponent() const;

	UFUNCTION()
	virtual void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

private:
	void PlayAttackAnimation();
	void AttackTrace();

	void StopAttack();
	void StopAttackTrace();

	void HandleStun();

	void StartStun();
	void FinishStun();

	void SetSensesEnabled(const bool IsEnabled);

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAIPerceptionComponent> AIPerceptionComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	FName IsPlayerOnSightName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	FName IsPursuingPlayerName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	FName HitLocationKeyName;

	UPROPERTY(
		EditDefaultsOnly, BlueprintReadWrite,
		Category = "AI|Attack", DisplayName="Damage",
		meta = (AllowPrivateAccess = "true")
	)
	float AttackDamage = 0.f;

	UPROPERTY(
		EditDefaultsOnly, BlueprintReadWrite,
		Category = "AI|Attack", DisplayName="Start Hit Socket",
		meta = (AllowPrivateAccess = "true")
	)
	FName AttackStartSocketName;

	UPROPERTY(
		EditDefaultsOnly, BlueprintReadWrite,
		Category = "AI|Attack", DisplayName="End Hit Socket",
		meta = (AllowPrivateAccess = "true")
	)
	FName AttackEndSocketName;

	// Rate of attack line trace, in seconds
	UPROPERTY(
		EditDefaultsOnly, BlueprintReadWrite,
		Category = "AI|Attack", DisplayName= "Trace Rate",
		meta = (AllowPrivateAccess = "true")
	)
	float AttackTraceRate = 0.01f;

	UPROPERTY(
		EditDefaultsOnly, BlueprintReadWrite,
		Category = "AI|Attack", DisplayName= "Animation montage",
		meta = (AllowPrivateAccess = "true")
	)
	TObjectPtr<UAnimMontage> AttackAnimation;

	UPROPERTY()
	FTimerHandle AttackTraceTimerHandle;

	UPROPERTY()
	FTimerHandle AttackAnimationTimerHandle;

	/*
	 * Duration of stun
	 * If less than animation duration, animation duration time will be used instead
	 */
	UPROPERTY(
		EditDefaultsOnly, BlueprintReadWrite,
		Category = "AI|Stun",
		meta = (AllowPrivateAccess = "true")
	)
	float StunDuration;

	UPROPERTY(
		VisibleAnywhere, BlueprintReadOnly,
		Category = "AI|Stun",
		meta = (AllowPrivateAccess = "true")
	)
	bool IsStunned;

	UPROPERTY(
		EditDefaultsOnly, BlueprintReadWrite,
		Category = "AI|Stun", DisplayName= "Animation montage",
		meta = (AllowPrivateAccess = "true")
	)
	TObjectPtr<UAnimMontage> StunAnimation;
	
	UPROPERTY()
	FTimerHandle StunTimerHandle;
};
